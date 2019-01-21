#pragma once
#include "stdafx.h"

namespace Mungus {

	class Actor;

	struct Line;

	struct HitBox {
		unsigned long actor;

		std::shared_ptr<Mungus::HitBox> parent = nullptr;
		std::shared_ptr<Mungus::HitBox> left = nullptr;
		std::shared_ptr<Mungus::HitBox> right = nullptr;

		MungusMath::MVec3 leftBound;
		MungusMath::MVec3 rightBound;

		bool isLeaf(void) const { return actor != 0; }
	};

	class MUNGUS AABBTree {
		std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>>* actors;
		std::shared_ptr<HitBox> root;

	public:
		AABBTree(std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>>* actors);
		virtual ~AABBTree();

		void buildTree(void);
		void emptyTree(void);
		void insert(unsigned long entityId);
		void remove(unsigned long entityId);
		
		bool intersect(const HitBox& first, const HitBox& second) const;
		bool intersect(const HitBox& box, const Mungus::Line& line) const;
		float surfaceArea(const HitBox& hitBox) const;
		float hypotheticalSurfaceArea(const HitBox& firstHitBox, const HitBox& secondHitBox) const;

		void setBoundsFromChildren(std::shared_ptr<HitBox> hitBox);

		void minimizeParentSizes(std::shared_ptr<HitBox> hitBox);

		unsigned long findFirstIntersecting(const Line& line);
	};


}
