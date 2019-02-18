#pragma once
#include "stdafx.h"


namespace Mungus {
	class Asset;

	// anything that exists in the world
	class MUNGUS Entity {
	private:

	protected:
		MungusMath::MVec3 position;
		MungusMath::MMat4 orientation;

	public:
		Entity(void);
		virtual ~Entity() {}

		const MungusMath::MVec3 getPosition(void) const;
		const MungusMath::MMat4 getOrientation(void) const;

		void rotate(const MungusMath::MVec3& axis, float angle);
		void pitch(float angle);
		void roll(float angle);
		void turn(float angle);

		const MungusMath::MVec3 forward(void) const;
		const MungusMath::MVec3 up(void) const;
		const MungusMath::MVec3 right(void) const;
		const MungusMath::MVec3	planarForward(void) const;
		const MungusMath::MVec3 planarUp(void) const;
		const MungusMath::MVec3	planarRight(void) const;

		void setPosition(const MungusMath::MVec3& newPos);
	};

}
