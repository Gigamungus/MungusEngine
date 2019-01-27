#include "stdafx.h"
#include "Camera.h"
#include "Actor.h"
#include "AABBTree.h"
#include "Application.h"


Mungus::Camera::Camera() :
	Mungus::Entity(),
	rotationSpeed(360.0f),
	movementSpeed(20.0f),
	strafing(MSTATIONARY),
	advancing(MSTATIONARY),
	ascending(MSTATIONARY),
	turning(MSTATIONARY),
	pitching(MSTATIONARY),
	rolling(MSTATIONARY),
	farRenderDistance(1000.0f),
	nearRenderDistance(0.01f),
	fieldOfView(90.0f),
	aspectRatio(1)
	{}

Mungus::Camera::~Camera() {}

const MungusMath::MMat4 Mungus::Camera::viewMatrix(void) const {
	return MungusMath::inverseMatrix(orientation) * MungusMath::MMat4::translate(-position.x, -position.y, -position.z);
}

const MungusMath::MMat4 Mungus::Camera::perspectiveMatrix() const {
	MungusMath::MMat4 perspectiveMat = MungusMath::MMat4::identity();
	float cotanHalfAngle = 1 / tanf(MungusMath::degToRads(fieldOfView) / 2.0f);


	perspectiveMat[0][0] = (aspectRatio * cotanHalfAngle);
	perspectiveMat[1][1] = cotanHalfAngle;
	perspectiveMat[2][2] = (farRenderDistance + nearRenderDistance) / (farRenderDistance - nearRenderDistance);
	perspectiveMat[3][2] = -1;
	perspectiveMat[2][3] = (2 * farRenderDistance * nearRenderDistance) / (farRenderDistance - nearRenderDistance);
	perspectiveMat[3][3] = 0;

	return perspectiveMat;
}

const float Mungus::Camera::getRotationSpeed(void) const {
	return rotationSpeed;
}

MungusMath::Line Mungus::Camera::getRayFromCursorLocation(const Mungus::CursorLocation& cursorLocation, float windowWidth, float windowHeight) const {
	auto orientation = getOrientation();


	float farWidth = 2 * farRenderDistance * aspectRatio * tanf(MungusMath::degToRads(fieldOfView / 2.0f));
	float farHeight = 2 * farRenderDistance * tanf(MungusMath::degToRads(fieldOfView / 2.0f));

	float x = 2.0f * ((cursorLocation.xpos - (windowWidth / 2.0f)) / windowWidth);
	float y = 2.0f * (((windowHeight / 2.0f) - cursorLocation.ypos) / windowHeight);


	MungusMath::MVec4 directionVector = orientation * MungusMath::MVec4{
		x * farWidth / 2,
		y * farHeight / 2,
		-farRenderDistance,
		1.0f
	};


	MungusMath::MVec3 unitDirectionVector = MungusMath::MVec3::normalize(MungusMath::MVec3{ directionVector.x, directionVector.y, directionVector.z });

	return MungusMath::Line{ getPosition(), unitDirectionVector };
}

bool Mungus::Camera::visible(const Actor& actor) const {
	std::shared_ptr<Mungus::HitBox> hitBox = actor.getHitBox();
	MungusMath::MVec3 relativeActorPosition = actor.getPosition() - position;
	float radius = hitBox->radius();
	MungusMath::MVec3 cameraForward = forward();
	MungusMath::MVec3 cameraRight = right();
	MungusMath::MVec3 cameraUp = up();

	return (
		   cameraForward.dot(relativeActorPosition) + nearRenderDistance + radius > 0 // close frustum side
		&& (cameraForward * -1.0f).dot(relativeActorPosition) + farRenderDistance + radius > 0 // far frustum side
		&& (MungusMath::rotateAboutAxis(cameraRight, cameraUp, -fieldOfView / (2 * aspectRatio)).dot(relativeActorPosition)) + radius > 0 // left frustum side
		&& (MungusMath::rotateAboutAxis(cameraRight * -1.0f, cameraUp, fieldOfView / (2 * aspectRatio)).dot(relativeActorPosition)) + radius > 0 // right frustum side
		&& (MungusMath::rotateAboutAxis(cameraUp, cameraRight, fieldOfView / 2).dot(relativeActorPosition)) + radius > 0 // bottom frustum side
		&& (MungusMath::rotateAboutAxis(cameraUp * -1.0f, cameraRight, -fieldOfView / 2).dot(relativeActorPosition)) + radius > 0 // top frustum side
	);
}
