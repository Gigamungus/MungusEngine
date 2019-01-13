#include "stdafx.h"
#include "Camera.h"


Mungus::Camera::Camera() :
	Mungus::Entity()
	{}

Mungus::Camera::~Camera() {

}

const MungusMath::MMat4 Mungus::Camera::viewMatrix(void) const {
	return MungusMath::inverseMatrix(MungusMath::MMat4::translate(position.x, position.y, position.z) * orientation);

	//auto forward4 = orientation * MungusMath::MVec4{ 0, 0, -1, 1 };
	//auto up4 = orientation * MungusMath::MVec4{ 0, 1, 0, 1 };
	//auto right4 = orientation * MungusMath::MVec4{ 1, 0, 0, 1 };

	//auto forward = MungusMath::MVec3::normalize(MungusMath::MVec3{ forward4.x, forward4.y, forward4.z });
	//auto up = MungusMath::MVec3::normalize(MungusMath::MVec3{ up4.x, up4.y, up4.z });
	//auto right = MungusMath::MVec3::normalize(MungusMath::MVec3{ right4.x, right4.y, right4.z });


	//return	MungusMath::MMat4{
	//			right.x,	right.y,	right.z,	0,
	//			up.x,		up.y,		up.z,		0,
	//			forward.x,	forward.y,	forward.z,	0,
	//			0,			0,			0,			1
	//} *MungusMath::MMat4::translate(-position.x, -position.y, -position.z);

}

const MungusMath::MMat4 Mungus::Camera::perspectiveMatrix(float angle, float ratio, float near, float far) const {
	MungusMath::MMat4 perspectiveMat = MungusMath::MMat4::identity();
	float aTanHalfAngle = atanf(angle / 2.0f);


	perspectiveMat[0][0] = (ratio * aTanHalfAngle);
	perspectiveMat[1][1] = aTanHalfAngle;
	perspectiveMat[2][2] = -(far + near) / (far - near);
	perspectiveMat[2][3] = -1;
	perspectiveMat[3][2] = -(2 * far * near) / (far - near);
	perspectiveMat[3][3] = 0;

	return MungusMath::transposeMatrix(perspectiveMat);
}
