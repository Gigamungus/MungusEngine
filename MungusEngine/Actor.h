#pragma once
#include "stdafx.h"
#include "Entity.h"

namespace Mungus {
	class Asset;
	struct Primitive;
	struct RenderInfo;
	struct HitBox;

	// anything that can be rendered and/or have physics applied
	class MUNGUS Actor : public Entity {
	private:
		std::string name;
		unsigned long id;
		bool physicsEnabled;
		const RenderInfo* renderInfo;
		MungusMath::MVec3 scale;
		MungusMath::MVec3 backHitboxCoord;
		MungusMath::MVec3 frontHitboxCoord;

	public:
		Actor(const Mungus::Asset& base, unsigned long id);
		virtual ~Actor() {};

		const std::string inline getName(void) const { return name; }
		const MungusMath::MVec3& getScale(void) const;
		const RenderInfo inline getRenderInfo(void) const;
		const std::shared_ptr<Mungus::HitBox> inline getHitBox(void) const;

		void scaleBy(float x, float y, float z);

		const MungusMath::MMat4 modelMatrix(void) const;
	};
}