#include "stdafx.h"
#include "Camera.h"


Mungus::Camera::Camera() :
	Mungus::Entity(),
	rotationSpeed(360.0f),
	movementSpeed(20.0f),
	strafing(MSTATIONARY),
	advancing(MSTATIONARY),
	ascending(MSTATIONARY),
	turning(MSTATIONARY),
	pitching(MSTATIONARY),
	rolling(MSTATIONARY)
	{}

Mungus::Camera::~Camera() {}

const MungusMath::MMat4 Mungus::Camera::viewMatrix(void) const {
	return MungusMath::inverseMatrix(orientation) * MungusMath::MMat4::translate(-position.x, -position.y, -position.z);
}

const MungusMath::MMat4 Mungus::Camera::perspectiveMatrix(float angle, float ratio, float near, float far) const {
	MungusMath::MMat4 perspectiveMat = MungusMath::MMat4::identity();
	float cotanHalfAngle = 1 / tanf(MungusMath::degToRads(angle) / 2.0f);


	perspectiveMat[0][0] = (ratio * cotanHalfAngle);
	perspectiveMat[1][1] = cotanHalfAngle;
	perspectiveMat[2][2] = (far + near) / (far - near);
	perspectiveMat[3][2] = -1;
	perspectiveMat[2][3] = (2 * far * near) / (far - near);
	perspectiveMat[3][3] = 0;

	return perspectiveMat;
}

const float Mungus::Camera::getRotationSpeed(void) const {
	return rotationSpeed;
}
