#include "stdafx.h"
#include "AABBTree.h"
#include "Actor.h"



Mungus::AABBTree::AABBTree(std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>>* actors) :
	actors(actors),
	root(nullptr)
{}

Mungus::AABBTree::~AABBTree() {}

void Mungus::AABBTree::buildTree(void) {
	emptyTree();

	for (auto actor : *actors) {
		insert(actor.first);
	}
}

void Mungus::AABBTree::emptyTree(void) {
	for (auto actor : *actors) {
		remove(actor.first);
	}
}

void Mungus::AABBTree::insert(unsigned long entityId) {
	std::shared_ptr<HitBox> actorBox = actors->at(entityId)->getHitBox();

	if (root == nullptr) {
		root = actorBox;
		return;
	}

	std::shared_ptr<HitBox> current = root;
	std::shared_ptr<HitBox> parent = root;

	while (!current->isLeaf()) {

		if (hypotheticalSurfaceArea(*current->left, *actorBox) < hypotheticalSurfaceArea(*current->right, *actorBox)) {
			parent = current;
			current = current->left;
		}
		else {
			parent = current;
			current = current->right;
		}

	}

	std::shared_ptr<HitBox> newBranch = std::make_shared<HitBox>(Mungus::HitBox{ 0, parent, current, actorBox });

	newBranch->left->parent = newBranch;
	newBranch->right->parent = newBranch;

	if (parent == root && current == parent) {
		root = newBranch;
		root->parent = nullptr;
	}
		
	else {
		if (parent->left == current)
			parent->left = newBranch;
		else
			parent->right = newBranch;

	}

	setBoundsFromChildren(newBranch);
	minimizeParentSizes(newBranch);

}

void Mungus::AABBTree::remove(unsigned long entityId) {
	if (root == nullptr) {
		MLOG("tried to remove entity from tree when tree was empty: " << entityId)
		return;
	}

	std::shared_ptr<HitBox> actorBox = actors->at(entityId)->getHitBox();

	std::queue<std::shared_ptr<Mungus::HitBox>> collidors = std::queue<std::shared_ptr<Mungus::HitBox>>();
	collidors.push(root);

	while (!collidors.empty() && collidors.front()->actor != entityId) {
		if (intersect(*actorBox, *collidors.front()->left))
			collidors.push(collidors.front()->left);

		if (intersect(*actorBox, *collidors.front()->right))
			collidors.push(collidors.front()->right);

		collidors.pop();
	}

	if (collidors.empty()) {
		MLOG("tried to remove entity from AABBTree that was not present: " << entityId)
	}

	else {
		std::shared_ptr<Mungus::HitBox> node = collidors.front();
		std::shared_ptr<Mungus::HitBox> leafToMove = nullptr;

		// node is root, empty tree
		if (node->parent == nullptr)
			root = nullptr;

		// node is child of root, replace root with its other child
		else if (node->parent->parent == nullptr) {
			if (node == node->parent->left) {
				root->left = nullptr;
				root = root->right;
			}
			else {
				root->right = nullptr;
				root = root->left;
			}

			root->parent = nullptr;
		}
		// node is child of a left node, replace grandparent's left node with the removed node's sibling
		else if (node->parent == node->parent->parent->left) {
			// node is a left node
			if (node == node->parent->left) {
				leafToMove = node->parent->right;
				node->parent->parent->left = node->parent->right;
				node->parent->right->parent = node->parent->parent;
				node->parent = nullptr;
			}
			// node is a right node
			else {
				leafToMove = node->parent->left;
				node->parent->parent->left = node->parent->left;
				node->parent->left->parent = node->parent->parent;
				node->parent = nullptr;
			}
		}
		// node is child of a right node, replace grandparent's right node with the removed node's sibling
		else {
			// node is a left node
			if (node == node->parent->left) {
				leafToMove = node->parent->right;
				node->parent->parent->right = node->parent->right;
				node->parent->right->parent = node->parent->parent;
				node->parent = nullptr;
			}
			// node is a right node
			else {
				leafToMove = node->parent->left;
				node->parent->parent->right = node->parent->left;
				node->parent->left->parent = node->parent->parent;
				node->parent = nullptr;
			}
		}

		if (leafToMove != nullptr) {
			minimizeParentSizes(leafToMove);
		}
	}
}

bool Mungus::AABBTree::intersect(const Mungus::HitBox& first, const Mungus::HitBox& second) const {
	return first.rightBound.x > second.leftBound.x && first.leftBound.x < second.rightBound.x &&
		first.rightBound.y > second.leftBound.y && first.leftBound.y < second.rightBound.y &&
		first.rightBound.z > second.leftBound.z && first.leftBound.z < second.rightBound.z;
}

float Mungus::AABBTree::surfaceArea(const HitBox & hitBox) const {
	float xWidth = hitBox.rightBound.x - hitBox.leftBound.x;
	float yWidth = hitBox.rightBound.y - hitBox.leftBound.y;
	float zWidth = hitBox.rightBound.z - hitBox.leftBound.z;
	return 2 * ((xWidth * yWidth) + (xWidth * zWidth) + (yWidth * zWidth));
}

float Mungus::AABBTree::hypotheticalSurfaceArea(const HitBox& firstHitBox, const HitBox& secondHitBox) const {
	float xWidth = MungusUtil::max(firstHitBox.rightBound.x, secondHitBox.rightBound.x) - MungusUtil::min(firstHitBox.leftBound.x, secondHitBox.leftBound.x);
	float yWidth = MungusUtil::max(firstHitBox.rightBound.y, secondHitBox.rightBound.y) - MungusUtil::min(firstHitBox.leftBound.y, secondHitBox.leftBound.y);
	float zWidth = MungusUtil::max(firstHitBox.rightBound.z, secondHitBox.rightBound.z) - MungusUtil::min(firstHitBox.leftBound.z, secondHitBox.leftBound.z);
	return 2 * ((xWidth * yWidth) + (xWidth * zWidth) + (yWidth * zWidth));
}

void Mungus::AABBTree::setBoundsFromChildren(std::shared_ptr<HitBox> hitBox) {
	if (!hitBox->isLeaf()) {

		hitBox->leftBound = MungusMath::MVec3{
			MungusUtil::min(hitBox->left->leftBound.x, hitBox->right->leftBound.x),
			MungusUtil::min(hitBox->left->leftBound.y, hitBox->right->leftBound.y),
			MungusUtil::min(hitBox->left->leftBound.z, hitBox->right->leftBound.z)
		};

		hitBox->rightBound = MungusMath::MVec3{
			MungusUtil::max(hitBox->left->rightBound.x, hitBox->right->rightBound.x),
			MungusUtil::max(hitBox->left->rightBound.y, hitBox->right->rightBound.y),
			MungusUtil::max(hitBox->left->rightBound.z, hitBox->right->rightBound.z)
		};

	}

	else {
		MLOG("setBoundsFromChildren on leaf node")
	}
}

void Mungus::AABBTree::minimizeParentSizes(std::shared_ptr<HitBox> hitBox) {
	std::shared_ptr<HitBox> current = hitBox;

	while (current->parent != nullptr) {
		setBoundsFromChildren(current->parent);
		current = current->parent;
	}
}
