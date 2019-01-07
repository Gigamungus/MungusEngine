#pragma once
#include "stdafx.h"


namespace Mungus {
	class Asset;

	class MUNGUS Entity {
	private:
		const unsigned int entityType;
		std::string name;

	protected:
		unsigned int programID;
		unsigned int vaoID;

	public:
		Entity(const Mungus::Asset& source);

		virtual ~Entity() {}

		const std::string inline getPath() const { return name; }
		const unsigned int inline type() const { return entityType; }
	};

}
