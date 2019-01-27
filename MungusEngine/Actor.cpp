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
	std::vector<MungusMath::MVec4> corners = std::vector<MungusMath::MVec4>();
	
	corners.push_back(MungusMath::MVec4{ backHitboxCoord.x, backHitboxCoord.y, -backHitboxCoord.z, 0 });
	corners.push_back(MungusMath::MVec4{ frontHitboxCoord.x, backHitboxCoord.y, -backHitboxCoord.z, 0 });
	corners.push_back(MungusMath::MVec4{ backHitboxCoord.x, backHitboxCoord.y, -frontHitboxCoord.z, 0 });
	corners.push_back(MungusMath::MVec4{ frontHitboxCoord.x, backHitboxCoord.y, -frontHitboxCoord.z, 0 });
	corners.push_back(MungusMath::MVec4{ backHitboxCoord.x, frontHitboxCoord.y, -backHitboxCoord.z, 0 });
	corners.push_back(MungusMath::MVec4{ frontHitboxCoord.x, frontHitboxCoord.y, -backHitboxCoord.z, 0 });
	corners.push_back(MungusMath::MVec4{ backHitboxCoord.x, frontHitboxCoord.y, -frontHitboxCoord.z, 0 });
	corners.push_back(MungusMath::MVec4{ frontHitboxCoord.x, frontHitboxCoord.y, -frontHitboxCoord.z, 0 });

	float lowx = std::numeric_limits<float>().infinity();
	float lowy = std::numeric_limits<float>().infinity();
	float lowz = std::numeric_limits<float>().infinity();
	float highx = -std::numeric_limits<float>().infinity();
	float highy = -std::numeric_limits<float>().infinity();
	float highz = -std::numeric_limits<float>().infinity();

	for (auto& corner : corners) {
		corner = getOrientation() * corner;

		if (corner.x < lowx)
			lowx = corner.x;
		else if (corner.x > highx)
			highx = corner.x;

		if (corner.y < lowy)
			lowy = corner.y;
		else if (corner.y > highy)
			highy = corner.y;

		if (corner.z < lowz)
			lowz = corner.z;
		else if (corner.z > highz)
			highz = corner.z;
	}



	return std::make_shared<Mungus::HitBox>(Mungus::HitBox{
		id,
		nullptr,
		nullptr,
		nullptr,
		(MungusMath::MVec3{lowx, lowy, lowz} *scale) + getPosition(), (MungusMath::MVec3{highx, highy, highz} *scale) + getPosition()
	});
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
