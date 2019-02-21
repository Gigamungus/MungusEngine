#include "stdafx.h"
#include "AABBTree.h"
#include "Camera.h"
#include "Actor.h"
#include "World.h"
#include "Asset.h"


template<typename T>
Mungus::AABBTree<T>::AABBTree() :
	root(nullptr),
	numElements(0),
	nextId(0)
{}

template<typename T>
Mungus::AABBTree<T>::~AABBTree() {
	emptyTree();
}

template<typename T>
void Mungus::AABBTree<T>::emptyTree(void) {
	for (auto actor : elements) {
		remove(actor.first);
	}
}

template<typename T>
unsigned long Mungus::AABBTree<T>::insert(unsigned long elementId) {

	std::shared_ptr<BoundingBox> boundingBox = elements.at(elementId)->getBoundingBox();
	boundingBox->elementId = elementId;

	if (root == nullptr) {
		root = boundingBox;
		return elementId;
	}

	std::shared_ptr<BoundingBox> current = root;
	std::shared_ptr<BoundingBox> parent = root;

	while (!current->isLeaf()) {
		float leftSurfaceArea = surfaceArea(current->left);
		float rightSurfaceArea = surfaceArea(current->right);

		if (hypotheticalSurfaceArea(current->left, boundingBox) - leftSurfaceArea <
			hypotheticalSurfaceArea(current->right, boundingBox) - rightSurfaceArea) {
			parent = current;
			current = current->left;
		}
		else {
			parent = current;
			current = current->right;
		}
	}

	std::shared_ptr<BoundingBox> newBranch = std::make_shared<BoundingBox>();
	
	{
		newBranch->parent = parent;
		newBranch->left = current;
		newBranch->right = boundingBox;
		newBranch->left->parent = newBranch;
		newBranch->right->parent = newBranch;
		setBoundsFromChildren(newBranch);
	}

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

	restoreAwesomeness(newBranch);

	return elementId;
}

template<typename T>
unsigned long Mungus::AABBTree<T>::insert(std::shared_ptr<T> element) {
	elements[++nextId] = element;
	return insert(nextId);
}

template<typename T>
void Mungus::AABBTree<T>::remove(unsigned long actorId) {
	if (root == nullptr) {
		MLOG("tried to remove entity from tree when tree was empty: " << actorId)
		return;
	}

	std::shared_ptr<BoundingBox> actorBox = elements.at(actorId)->getBoundingBox();

	std::queue<std::shared_ptr<Mungus::BoundingBox>> collidors = std::queue<std::shared_ptr<Mungus::BoundingBox>>();
	collidors.push(root);

	while (!collidors.empty() && collidors.front()->elementId != actorId) {
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
		std::shared_ptr<Mungus::BoundingBox> node = collidors.front();
		std::shared_ptr<Mungus::BoundingBox> leafToMove = nullptr;

		// node is root, empty tree
		if (node->parent == nullptr)
			root = nullptr;

		// node is child of root, replace root with its other child
		else if (node->parent->isRoot()) {
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
			restoreAwesomeness(leafToMove);
		}
	}
}

template<typename T>
bool Mungus::AABBTree<T>::intersect(const Mungus::BoundingBox& first, const Mungus::BoundingBox& second) const {
	return first.rightBound.x > second.leftBound.x && first.leftBound.x < second.rightBound.x &&
		first.rightBound.y > second.leftBound.y && first.leftBound.y < second.rightBound.y &&
		first.rightBound.z > second.leftBound.z && first.leftBound.z < second.rightBound.z;
}

template<typename T>
bool Mungus::AABBTree<T>::intersect(const BoundingBox & box, const MungusMath::Line & line) const {
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

template<typename T>
std::vector<std::shared_ptr<T>> Mungus::AABBTree<T>::getVisibleElements(const Mungus::Camera& camera) {
	std::vector<std::shared_ptr<T>> visibleElements;
	std::queue<std::shared_ptr<Mungus::BoundingBox>> candidates;
	candidates.push(root);

	while (!candidates.empty()) {
		std::shared_ptr<Mungus::BoundingBox> nextElement = candidates.front();
		candidates.pop();

		if (camera.visible(nextElement)) {
			if (nextElement->isLeaf()) {
				visibleElements.push_back(elements.at(nextElement->elementId));
			}
			else {
				candidates.push(nextElement->left);
				candidates.push(nextElement->right);
			}
		}
	}

	return visibleElements;
}

template<typename T>
float Mungus::AABBTree<T>::surfaceArea(std::shared_ptr<BoundingBox> boundingBox) const {
	float xWidth = boundingBox->rightBound.x - boundingBox->leftBound.x;
	float yWidth = boundingBox->rightBound.y - boundingBox->leftBound.y;
	float zWidth = boundingBox->rightBound.z - boundingBox->leftBound.z;
	return 2 * ((xWidth * yWidth) + (xWidth * zWidth) + (yWidth * zWidth));
}

template<typename T>
float Mungus::AABBTree<T>::hypotheticalSurfaceArea(std::shared_ptr<BoundingBox> bBox1, std::shared_ptr<BoundingBox> bBox2) const {
	float xWidth = MungusUtil::max(bBox1->rightBound.x, bBox2->rightBound.x) - MungusUtil::min(bBox1->leftBound.x, bBox2->leftBound.x);
	float yWidth = MungusUtil::max(bBox1->rightBound.y, bBox2->rightBound.y) - MungusUtil::min(bBox1->leftBound.y, bBox2->leftBound.y);
	float zWidth = MungusUtil::max(bBox1->rightBound.z, bBox2->rightBound.z) - MungusUtil::min(bBox1->leftBound.z, bBox2->leftBound.z);
	return 2 * ((xWidth * yWidth) + (xWidth * zWidth) + (yWidth * zWidth));
}

template<typename T>
void Mungus::AABBTree<T>::setBoundsFromChildren(std::shared_ptr<BoundingBox> hitBox) {
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

template<typename T>
unsigned long Mungus::AABBTree<T>::findFirstIntersecting(const MungusMath::Line& line) {
	if (root == nullptr || !intersect(*root, line))
		return 0;

	std::queue<std::shared_ptr<Mungus::BoundingBox>> intersectingBranches = std::queue<std::shared_ptr<Mungus::BoundingBox>>();
	std::vector<unsigned long> intersectingActors;

	intersectingBranches.push(root);
	int i = 0;
	while (!intersectingBranches.empty()) {
		i++;
		if (intersectingBranches.front()->isLeaf()) {
			intersectingActors.push_back(intersectingBranches.front()->elementId);
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
		float actorDistance = (elements.at(id)->getPosition() - line.position).size();
		if (actorDistance < closestDistance) {
			closestActor = id;
			closestDistance = actorDistance;
		}
	}

	std::cout << "searched " << i << " items to find item: " << closestActor << "\n";
	return closestActor;
}

template<typename T>
const std::unordered_map<unsigned long, std::shared_ptr<T>> Mungus::AABBTree<T>::getActors(void) const {
	return elements;
}

template<typename T>
void Mungus::AABBTree<T>::setActorPosition(unsigned long id, const MungusMath::MVec3 & position) {
	remove(id);
	elements.at(id)->setPosition(position);
	insert(id);
}

template<typename T>
void Mungus::AABBTree<T>::scaleActor(unsigned long id, const MungusMath::MVec3 & scale) {
	remove(id);
	elements.at(id)->scaleBy(scale.x, scale.y, scale.z);
	insert(id);
}

template<typename T>
void Mungus::AABBTree<T>::rotateActor(unsigned long id, const MungusMath::MVec3 & axis, float angle) {
	remove(id);
	elements.at(id)->rotate(axis, angle);
	insert(id);
}

template<typename T>
void Mungus::AABBTree<T>::turnActor(unsigned long id, float angle) {
	remove(id);
	elements.at(id)->turn(angle);
	insert(id);
}

template<typename T>
void Mungus::AABBTree<T>::pitchActor(unsigned long id, float angle) {
	remove(id);
	elements.at(id)->pitch(angle);
	insert(id);
}

template<typename T>
void Mungus::AABBTree<T>::rollActor(unsigned long id, float angle) {
	remove(id);
	elements.at(id)->roll(angle);
	insert(id);
}

template<class T>
void Mungus::AABBTree<T>::restoreAwesomeness(std::shared_ptr<Mungus::BoundingBox> badNode) {
	while (badNode != nullptr) {
		if (!badNode->isLeaf()) {
			fixBoxHeight(badNode);
			setBoundsFromChildren(badNode);
			balanceNode(badNode);
		}
		badNode = badNode->parent;
	}
	while (root->parent != nullptr) {
		root = root->parent;
	}
}

template<class T>
void Mungus::AABBTree<T>::fixBoxHeight(std::shared_ptr<Mungus::BoundingBox> badNode) {
	if (badNode != nullptr) {
		int left = getBoxHeight(badNode->left);
		int right = getBoxHeight(badNode->right);
		badNode->height = left > right ? left + 1 : right + 1;
	}
}

template<class T>
int Mungus::AABBTree<T>::getBoxHeight(std::shared_ptr<Mungus::BoundingBox> node) const {
	return node == nullptr ? -1 : node->height;
}

template<typename T>
void Mungus::AABBTree<T>::balanceNode(std::shared_ptr<Mungus::BoundingBox> badNode) {
	if (badNode != nullptr) {
		std::shared_ptr<Mungus::BoundingBox> rightNode = badNode->right;
		std::shared_ptr<Mungus::BoundingBox> leftNode = badNode->left;

		// check case 1/2
		if (getBoxHeight(leftNode) - getBoxHeight(rightNode) > 1) {
			// case 2, swap to case 1
			if (getBoxHeight(leftNode->right) > getBoxHeight(leftNode->left)) {
				leftNode->swapChildren();
			}
			// now case 1
			badNode->setParentsChildTo(leftNode);
			badNode->left = leftNode->right;
			leftNode->right = badNode;
			leftNode->parent = badNode->parent;
			badNode->parent = leftNode;
			badNode->left->parent = badNode;

			setBoundsFromChildren(badNode);
			setBoundsFromChildren(leftNode);

			fixBoxHeight(badNode);
			fixBoxHeight(leftNode);
		}

		// check case 3/4
		if (getBoxHeight(rightNode) - getBoxHeight(leftNode) > 1) {
			// case 3, swap to case 4
			if (getBoxHeight(rightNode->left) > getBoxHeight(rightNode->right)) {
				rightNode->swapChildren();
			}
			// now case 4
			badNode->setParentsChildTo(rightNode);
			badNode->right = rightNode->left;
			rightNode->left = badNode;
			rightNode->parent = badNode->parent;
			badNode->parent = rightNode;
			badNode->right->parent = badNode;

			setBoundsFromChildren(badNode);
			setBoundsFromChildren(rightNode);

			fixBoxHeight(badNode);
			fixBoxHeight(rightNode);
		}
	}
}
