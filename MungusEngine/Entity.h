#pragma once
#include "stdafx.h"


namespace Mungus {
	class Asset;
	struct RenderInfo;

	class MUNGUS Entity {
	private:
		std::string name;
		const RenderInfo* renderInfo;

	public:
		Entity(const Mungus::Asset& source);

		virtual ~Entity() {}

		const std::string inline getName(void) const { return name; }
		const RenderInfo inline getRenderInfo(void) const;
	};

}
