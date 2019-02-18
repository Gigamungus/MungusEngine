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
	orientation = orientation * MungusMath::MMat4::rotation(axis.x, axis.y, -axis.z, angle);
}

void Mungus::Entity::pitch(float angle) {
	angle = -angle;
	auto rightVector = planarRight();
	float pitchAngle = MungusMath::radsToDeg(acosf(forward().dot(planarUp() * -1)));

	if (0.1f > pitchAngle - angle) {
		angle = pitchAngle - 0.1f;
	}

	if (pitchAngle - angle > 179.9f) {
		angle = pitchAngle - 179.9f;
	}
	//if (0.0 < pitchAngle - angle && pitchAngle - angle < 180.0) {
	orientation = MungusMath::MMat4::rotation(rightVector.x, rightVector.y, rightVector.z, angle) * orientation;
}

void Mungus::Entity::roll(float angle) {
	auto forward = orientation * MungusMath::MVec4{0, 0, -1, 1};
	orientation = orientation * MungusMath::MMat4::rotation(forward.x, forward.y, forward.z, angle);
}

void Mungus::Entity::turn(float angle) {
	orientation = MungusMath::MMat4::rotation(0, 1, 0, angle) * orientation;
}

const MungusMath::MVec3 Mungus::Entity::forward(void) const {
	MungusMath::MVec4 forward = orientation * MungusMath::MVec4{ 0, 0, -1, 1 };
	return MungusMath::MVec3::normalize(MungusMath::MVec3{ forward.x, forward.y, forward.z });
}

const MungusMath::MVec3 Mungus::Entity::up(void) const {
	return MungusMath::MVec3::normalize(forward().cross(right()));
}

const MungusMath::MVec3 Mungus::Entity::right(void) const {
	return MungusMath::MVec3::normalize(MungusMath::MVec3{ 0.0f, 1.0f, 0.0f }.cross(forward()));
}

const MungusMath::MVec3 Mungus::Entity::planarForward(void) const {
	auto forwardVector = forward();
	return MungusMath::MVec3::normalize(MungusMath::MVec3{forwardVector.x, 0, forwardVector.z});
}

const MungusMath::MVec3 Mungus::Entity::planarUp(void) const {
	return MungusMath::MVec3({0.0f, 1.0f, 0.0f});
}

const MungusMath::MVec3 Mungus::Entity::planarRight(void) const {
	auto rightVector = right();
	return MungusMath::MVec3::normalize({rightVector.x, 0.0f, rightVector.z});
}

void Mungus::Entity::setPosition(const MungusMath::MVec3& newPos) {
	position = { newPos.x, newPos.y, newPos.z };
}
