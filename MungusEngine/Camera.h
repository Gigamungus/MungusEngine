#pragma once
#include "Entity.h"

namespace Mungus {
	
	class Camera : public Entity {
	private:

	public:
		Camera();
		virtual ~Camera();

		const MungusMath::MMat4 viewMatrix(void) const;
		const MungusMath::MMat4 perspectiveMatrix(float angle, float ratio, float near, float far) const;
	};

}