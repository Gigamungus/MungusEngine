#pragma once
#include "stdafx.h"
#include "Entity.h"

namespace Mungus {

	class MUNGUS Actor : public Entity {
	private:

	public:
		Actor(const std::string& assetPath) : Mungus::Entity(assetPath)  {};
		virtual ~Actor() {};
	};

}