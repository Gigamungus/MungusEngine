#pragma once
#include "stdafx.h"

namespace Mungus {

	class Actor;
	class Asset;

	struct HitBox {
		unsigned long actor;

		std::shared_ptr<Mungus::HitBox> parent = nullptr;
		std::shared_ptr<Mungus::HitBox> left = nullptr;
		std::shared_ptr<Mungus::HitBox> right = nullptr;

		MungusMath::MVec3 leftBound;
		MungusMath::MVec3 rightBound;

		inline bool isLeaf(void) const { return actor != 0; }

		inline float radius(void) const {
			return MungusMath::MVec3{
				(rightBound.x - leftBound.x) / 2, (rightBound.y - leftBound.y) / 2, (rightBound.z - leftBound.z) / 2
			}.size();
		}
	};

	class MUNGUS AABBTree {
		std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>> actors;
		unsigned long actorCount;
		std::shared_ptr<HitBox> root;

	public:
		AABBTree();
		virtual ~AABBTree();

		void emptyTree(void);
		unsigned long insert(unsigned long entityId);
		unsigned long insert(std::shared_ptr<Mungus::Asset> base);
		void remove(unsigned long entityId);
		
		bool intersect(const HitBox& first, const HitBox& second) const;
		bool intersect(const HitBox& box, const MungusMath::Line& line) const;
		float surfaceArea(const HitBox& hitBox) const;
		float hypotheticalSurfaceArea(const HitBox& firstHitBox, const HitBox& secondHitBox) const;

		void setBoundsFromChildren(std::shared_ptr<HitBox> hitBox);

		void minimizeParentSizes(std::shared_ptr<HitBox> hitBox);

		unsigned long findFirstIntersecting(const MungusMath::Line& line);

		const std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>> getActors(void) const;

		void setActorPosition(unsigned long id, const MungusMath::MVec3& position);
		void scaleActor(unsigned long id, const MungusMath::MVec3& scale);
		void rotateActor(unsigned long id, const MungusMath::MVec3& axis, float angle);
		void turnActor(unsigned long id, float angle);
		void pitchActor(unsigned long id, float angle);
		void rollActor(unsigned long id, float angle);
	};


}
