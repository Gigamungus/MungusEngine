#pragma once
#include "Entity.h"

namespace Mungus {
	
	class Camera : public Entity {
	private:
		float rotationSpeed;
		float movementSpeed;

	public:
		int strafing;
		int ascending;
		int advancing;
		int turning;
		int pitching;
		int rolling;

		Camera();
		virtual ~Camera();

		const MungusMath::MMat4 viewMatrix(void) const;
		const MungusMath::MMat4 perspectiveMatrix(float angle, float ratio, float near, float far) const;

		inline float getRotationSpeed(void) const { return rotationSpeed; }
		inline void setRotationSpeed(float speed) { rotationSpeed = speed; }

		inline float getMovementSpeed(void) const { return movementSpeed; }
		inline void setMovementSpeed(float speed) { movementSpeed = speed; }


	};

}