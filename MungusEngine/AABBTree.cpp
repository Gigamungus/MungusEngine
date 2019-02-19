#include "stdafx.h"
#include "AABBTree.h"
#include "Actor.h"
#include "World.h"
#include "Asset.h"


Mungus::AABBTree::AABBTree() :
	root(nullptr),
	actorCount(0)
{}

Mungus::AABBTree::~AABBTree() {}

void Mungus::AABBTree::emptyTree(void) {
	for (auto actor : actors) {
		remove(actor.first);
	}
}

unsigned long Mungus::AABBTree::insert(unsigned long actorId) {

	std::shared_ptr<HitBox> actorBox = actors.at(actorId)->getHitBox();

	if (root == nullptr) {
		root = actorBox;
		return actorId;
	}

	std::shared_ptr<HitBox> current = root;
	std::shared_ptr<HitBox> parent = root;

	while (!current->isLeaf()) {
		float leftSurfaceArea = surfaceArea(*current->left);
		float rightSurfaceArea = surfaceArea(*current->right);

		if (hypotheticalSurfaceArea(*current->left, *actorBox) - leftSurfaceArea > hypotheticalSurfaceArea(*current->right, *actorBox) - rightSurfaceArea) {
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

	return actorId;
}

unsigned long Mungus::AABBTree::insert(std::shared_ptr<Mungus::Asset> base) {
	actors[actorCount] = std::make_shared<Mungus::Actor>(Mungus::Actor(*base, ++actorCount));

	return insert(actorCount);
}

void Mungus::AABBTree::remove(unsigned long actorId) {
	if (root == nullptr) {
		MLOG("tried to remove entity from tree when tree was empty: " << actorId)
		return;
	}

	std::shared_ptr<HitBox> actorBox = actors.at(actorId)->getHitBox();

	std::queue<std::shared_ptr<Mungus::HitBox>> collidors = std::queue<std::shared_ptr<Mungus::HitBox>>();
	collidors.push(root);

	while (!collidors.empty() && collidors.front()->actor != actorId) {
		if (!collidors.front()->isLeaf()) {
			if (intersect(*actorBox, *collidors.front()->left))
				collidors.push(collidors.front()->left);

			if (intersect(*actorBox, *collidors.front()->right))
				collidors.push(collidors.front()->right);
		}
		collidors.pop();
	}

	if (collidors.empty()) {
		MLOG("tried to remove entity from AABBTree that was not present: " << actorId)
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

bool Mungus::AABBTree::intersect(const HitBox & box, const MungusMath::Line & line) const {
	float vecsToLeftX	= (box.leftBound.x  - line.position.x) / line.direction.x;
	float vecsToLeftY	= (box.leftBound.y  - line.position.y) / line.direction.y;
	float vecsToLeftZ	= (box.leftBound.z  - line.position.z) / line.direction.z;
	float vecsToRightX	= (box.rightBound.x - line.position.x) / line.direction.x;
	float vecsToRightY	= (box.rightBound.y - line.position.y) / line.direction.y;
	float vecsToRightZ	= (box.rightBound.z - line.position.z) / line.direction.z;

	float minVecsToX = MungusUtil::min(vecsToLeftX, vecsToRightX);
	float minVecsToY = MungusUtil::min(vecsToLeftY, vecsToRightY);
	float minVecsToZ = MungusUtil::min(vecsToLeftZ, vecsToRightZ);
	float maxVecsToX = MungusUtil::max(vecsToLeftX, vecsToRightX);
	float maxVecsToY = MungusUtil::max(vecsToLeftY, vecsToRightY);
	float maxVecsToZ = MungusUtil::max(vecsToLeftZ, vecsToRightZ);

	float minVecs = MungusUtil::max3(minVecsToX, minVecsToY, minVecsToZ);
	float maxVecs = MungusUtil::min3(maxVecsToX, maxVecsToY, maxVecsToZ);

	return minVecs < maxVecs && maxVecs > 0;
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

unsigned long Mungus::AABBTree::findFirstIntersecting(const MungusMath::Line& line) {
	if (root == nullptr || !intersect(*root, line))
		return 0;

	std::queue<std::shared_ptr<Mungus::HitBox>> intersectingBranches = std::queue<std::shared_ptr<Mungus::HitBox>>();
	std::vector<unsigned long> intersectingActors;

	intersectingBranches.push(root);

	while (!intersectingBranches.empty()) {

		if (intersectingBranches.front()->isLeaf()) {
			intersectingActors.push_back(intersectingBranches.front()->actor);
		}
		else {
			if (intersect(*intersectingBranches.front()->left, line))
				intersectingBranches.push(intersectingBranches.front()->left);

			if (intersect(*intersectingBranches.front()->right, line))
				intersectingBranches.push(intersectingBranches.front()->right);

		}

		intersectingBranches.pop();
	}

	unsigned long closestActor = 0;
	float closestDistance = std::numeric_limits<float>::infinity();

	for (auto id : intersectingActors) {
		float actorDistance = (actors.at(id)->getPosition() - line.position).size();
		if (actorDistance < closestDistance) {
			closestActor = id;
			closestDistance = actorDistance;
		}
	}
	
	return closestActor;
}

const std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>> Mungus::AABBTree::getActors(void) const {
	return actors;
}

void Mungus::AABBTree::setActorPosition(unsigned long id, const MungusMath::MVec3 & position) {
	remove(id);
	actors.at(id)->setPosition(position);
	insert(id);
}

void Mungus::AABBTree::scaleActor(unsigned long id, const MungusMath::MVec3 & scale) {
	remove(id);
	actors.at(id)->scaleBy(scale.x, scale.y, scale.z);
	insert(id);
}

void Mungus::AABBTree::rotateActor(unsigned long id, const MungusMath::MVec3 & axis, float angle) {
	remove(id);
	actors.at(id)->rotate(axis, angle);
	insert(id);
}

void Mungus::AABBTree::turnActor(unsigned long id, float angle) {
	remove(id);
	actors.at(id)->turn(angle);
	insert(id);
}

void Mungus::AABBTree::pitchActor(unsigned long id, float angle) {
	remove(id);
	actors.at(id)->pitch(angle);
	insert(id);
}

void Mungus::AABBTree::rollActor(unsigned long id, float angle) {
	remove(id);
	actors.at(id)->roll(angle);
	insert(id);
}
