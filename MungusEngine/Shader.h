#pragma once
#include "stdafx.h"

namespace Mungus {
	
	class VLO;

	class Shader {
	private:
		unsigned int id;
		std::shared_ptr<VLO> layout;

	public:
		Shader(const json& source);
		virtual ~Shader();
		const unsigned int inline getId(void) const { return id; }
		VLO& getLayout(void) const { return *layout; }
	};

}
