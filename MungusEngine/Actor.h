#pragma once
#include "stdafx.h"
#include "Entity.h"

namespace Mungus {
	class Asset;
	struct Primitive;
	struct BoundingBox;

	// anything that can be rendered and/or have physics applied
	class MUNGUS Actor : public Entity {
	private:
		unsigned long id;
		const Mungus::Asset& source;
		bool physicsEnabled;
		MungusMath::MVec3 scale;
		std::string currentAnimation;
		unsigned long animationFrame;

	public:
		Actor(const Mungus::Asset& base);
		virtual ~Actor() {};

		const std::string getName(void) const;
		const MungusMath::MVec3& getScale(void) const;
		const std::shared_ptr<Mungus::BoundingBox> inline getBoundingBox(void) const;
		unsigned long getId(void) const { return id; }
		unsigned long getVAOId(void) const;
		unsigned long getProgramId(void) const;
		int numTriangleVertices(void) const;

		void scaleBy(float x, float y, float z);

		const MungusMath::MMat4 modelMatrix(void) const;
	};
}