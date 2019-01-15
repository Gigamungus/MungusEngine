#include "stdafx.h"
#include "Entity.h"
#include "Asset.h"

Mungus::Entity::Entity() :
	position({ 0, 0, 0 }),
	orientation({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1})
{}

const MungusMath::MVec3 Mungus::Entity::getPosition(void) const {
	return position;
}

const MungusMath::MMat4 Mungus::Entity::getOrientation(void) const {
	return orientation;
}

void Mungus::Entity::rotate(const MungusMath::MVec3 & axis, float angle) {
	orientation = orientation * MungusMath::MMat4::rotation(axis.x, axis.y, axis.z, angle);
}

void Mungus::Entity::pitch(float angle) {
	auto right = orientation * MungusMath::MVec4{ 1, 0, 0, 1 };
	orientation = orientation * MungusMath::MMat4::rotation(right.x, right.y, right.z, angle);
}

void Mungus::Entity::roll(float angle) {
	auto forward = orientation * MungusMath::MVec4{0, 0, -1, 1};
	orientation = orientation * MungusMath::MMat4::rotation(forward.x, forward.y, forward.z, angle);
}

void Mungus::Entity::turn(float angle) {
	orientation = MungusMath::MMat4::rotation(0, 1, 0, angle) * orientation;
}

void Mungus::Entity::setPosition(const MungusMath::MVec3& newPos) {
	position = { newPos.x, newPos.y, newPos.z };
}
