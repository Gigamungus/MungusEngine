#pragma once
#include "stdafx.h"


namespace Mungus {
	class Asset;
	struct RenderInfo;

	class MUNGUS Entity {
	private:
		std::string name;
		unsigned long id;
		const RenderInfo* renderInfo;

		MungusMath::MMat4 scale;
		MungusMath::MMat4 orientation;
		MungusMath::MMat4 position;

	public:
		Entity(const Mungus::Asset& source, unsigned long id);

		virtual ~Entity() {}

		const std::string inline getName(void) const { return name; }
		const RenderInfo inline getRenderInfo(void) const;
	};

}
