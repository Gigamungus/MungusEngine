#pragma once
#include "stdafx.h"

namespace Mungus {

	class Actor;
	class Asset;

	struct BoundingBox {
		unsigned long elementId;
		MungusMath::MVec3 leftBound;
		MungusMath::MVec3 rightBound;

		unsigned long height;
		std::shared_ptr<Mungus::BoundingBox> parent = nullptr;
		std::shared_ptr<Mungus::BoundingBox> left = nullptr;
		std::shared_ptr<Mungus::BoundingBox> right = nullptr;

		BoundingBox() : elementId(0), height(1) {}
		BoundingBox(unsigned long elementId, MungusMath::MVec3 lowerBound, MungusMath::MVec3 upperBound) :
			elementId(elementId),
			leftBound(lowerBound),
			rightBound(upperBound),
			height(0)
		{}
		inline bool isLeaf(void) const { return elementId != 0; }
		inline bool isRoot(void) const { return parent == nullptr; }
		inline void swapChildren() {
			std::shared_ptr<Mungus::BoundingBox> tmp = left;
			left = right;
			right = tmp;
		};
		inline void setParentsChildTo(std::shared_ptr<Mungus::BoundingBox> newChild) {
			if (!isRoot()) {
				if (&*parent->left == this) {
					parent->left = newChild;
				}
				else {
					parent->right = newChild;
				}
			}
		}
		inline float radius(void) const {
			return MungusMath::MVec3{
				(rightBound.x - leftBound.x), (rightBound.y - leftBound.y), (rightBound.z - leftBound.z)
			}.size() / 2;
		}
	};

	template <typename T>
	class MUNGUS AABBTree {
		std::unordered_map<unsigned long, std::shared_ptr<T>> elements;
		unsigned long numElements;
		unsigned long nextId;
		std::shared_ptr<BoundingBox> root;


		unsigned long insert(unsigned long entityId);


	public:
		AABBTree();
		virtual ~AABBTree();

		unsigned long insert(std::shared_ptr<T> element);
		void remove(unsigned long entityId);
		void emptyTree(void);
		unsigned long findFirstIntersecting(const MungusMath::Line& line);
		
		bool intersect(const BoundingBox& first, const BoundingBox& second) const;
		bool intersect(const BoundingBox& box, const MungusMath::Line& line) const;


		// todo: make these private
		float surfaceArea(std::shared_ptr<BoundingBox> hitBox) const;
		float hypotheticalSurfaceArea(std::shared_ptr<BoundingBox> firstHitBox, std::shared_ptr<BoundingBox> secondHitBox) const;
		void setBoundsFromChildren(std::shared_ptr<BoundingBox> hitBox);
		const std::unordered_map<unsigned long, std::shared_ptr<T>> getActors(void) const;
		void restoreAwesomeness(std::shared_ptr<Mungus::BoundingBox> badNode);
		void fixBoxHeight(std::shared_ptr<Mungus::BoundingBox> badNode);
		void balanceNode(std::shared_ptr<Mungus::BoundingBox> badNode);
		int getBoxHeight(std::shared_ptr<Mungus::BoundingBox> node) const;

		// todo: template specialize these
		void setActorPosition(unsigned long id, const MungusMath::MVec3& position);
		void scaleActor(unsigned long id, const MungusMath::MVec3& scale);
		void rotateActor(unsigned long id, const MungusMath::MVec3& axis, float angle);
		void turnActor(unsigned long id, float angle);
		void pitchActor(unsigned long id, float angle);
		void rollActor(unsigned long id, float angle);
	};


	template class AABBTree<Mungus::Actor>;
}

