#pragma once
#include "stdafx.h"

namespace Mungus {

	class VLO;

	class VBO {
	private:
		unsigned int id;

	public:
		VBO(const VLO& layout, const std::vector<json>& vertices);
		virtual ~VBO();
	};

}
