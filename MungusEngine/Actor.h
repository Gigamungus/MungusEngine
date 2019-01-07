#pragma once
#include "stdafx.h"
#include "Entity.h"

namespace Mungus {
	class Asset;
	struct Primitive;

	class MUNGUS Actor : public Entity {
	private:
		std::shared_ptr<std::vector<Mungus::Primitive>> primitives;

	public:
		Actor(const Mungus::Asset& base);
		virtual ~Actor() {};
	};
}