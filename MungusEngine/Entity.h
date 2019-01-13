#pragma once
#include "stdafx.h"


namespace Mungus {
	class Asset;

	class MUNGUS Entity {
	private:

	protected:
		MungusMath::MVec3 position;
		MungusMath::MMat4 orientation;

	public:
		Entity();
		virtual ~Entity() {}

		const MungusMath::MVec3 getPosition(void) const;
		const MungusMath::MMat4 getOrientation(void) const;

		void rotate(const MungusMath::MVec3& axis, float angle);
		void pitch(float angle);
		void roll(float angle);
		void turn(float angle);

		void setPosition(const MungusMath::MVec3& newPos);
	};

}
