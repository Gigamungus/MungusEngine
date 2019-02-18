#pragma once
#include "stdafx.h"

namespace Mungus {
	class Shader;
	class VAO;

	class MUNGUS Asset {
	public:
		std::string assetName;
		std::shared_ptr<VAO> vao;
		json hitboxCoords;
		std::shared_ptr<Shader> program;

		Asset() : program(nullptr) {};
		Asset(	const std::string& name,
				const std::unordered_map<std::string, Shader>& programs);
		virtual ~Asset() {}
	};
}
