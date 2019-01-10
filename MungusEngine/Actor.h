#pragma once
#include "stdafx.h"
#include "Entity.h"

namespace Mungus {
	class Asset;
	struct Primitive;

	class MUNGUS Actor : public Entity {

	public:
		Actor(const Mungus::Asset& base, unsigned long id);
		virtual ~Actor() {};
	};
}