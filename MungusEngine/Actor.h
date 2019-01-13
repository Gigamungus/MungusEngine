#pragma once
#include "stdafx.h"
#include "Entity.h"

namespace Mungus {
	class Asset;
	struct Primitive;
	struct RenderInfo;

	class MUNGUS Actor : public Entity {
	private:
		std::string name;
		unsigned long id;
		const RenderInfo* renderInfo;
		MungusMath::MVec3 scale;

	public:
		Actor(const Mungus::Asset& base, unsigned long id);
		virtual ~Actor() {};

		const std::string inline getName(void) const { return name; }
		const MungusMath::MVec3& getScale(void) const;
		const RenderInfo inline getRenderInfo(void) const;

		void scaleBy(float x, float y, float z);

		const MungusMath::MMat4 modelMatrix(void) const;
	};
}