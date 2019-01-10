#pragma once
#include "stdafx.h"


namespace Mungus {
	class Asset;

	class MUNGUS Entity {
	private:

	protected:
		MungusMath::MMat4 orientation;
		MungusMath::MVec3 position;

	public:

		Entity();
		virtual ~Entity() {}

	};

}
