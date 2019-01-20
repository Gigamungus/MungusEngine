#include "stdafx.h"
#include "Actor.h"
#include "Asset.h"
#include "AABBTree.h"


Mungus::Actor::Actor(const Mungus::Asset& source, unsigned long id) :
	name(source.assetName),
	id(id),
	renderInfo(&source.renderInfo),
	scale({1.0f, 1.0f, 1.0f}),
	physicsEnabled(false),
	backHitboxCoord(source.backHitboxCoord),
	frontHitboxCoord(source.frontHitboxCoord)
{}

const MungusMath::MVec3& Mungus::Actor::getScale(void) const {
	return scale;
}

const Mungus::RenderInfo inline Mungus::Actor::getRenderInfo(void) const {
	return *renderInfo;
}

inline const std::shared_ptr<Mungus::HitBox> Mungus::Actor::getHitBox(void) const {
	return std::make_shared<Mungus::HitBox>(Mungus::HitBox{id, nullptr, nullptr, nullptr, (backHitboxCoord * scale) + position, (frontHitboxCoord * scale) + position});
}

void Mungus::Actor::scaleBy(float x, float y, float z) {
	scale.x *= x;
	scale.y *= y;
	scale.z *= z;
}

const MungusMath::MMat4 Mungus::Actor::modelMatrix(void) const {
	return	MungusMath::MMat4::translate(position.x, position.y, position.z) *
			MungusMath::MMat4::scale(scale.x, scale.y, scale.z) *
			orientation;
}
