#pragma once
#include "Entity.h"

namespace Mungus {
	
	class Camera : public Entity {
	private:
		MungusMath::MVec3 up{ 0.0f, 1.0f, 0.0f };

	public:
		Camera();
		virtual ~Camera();



	};

}