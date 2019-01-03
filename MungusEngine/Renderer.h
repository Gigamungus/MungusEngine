#pragma once
#include "Core.h"
#include "pch.h"

namespace Mungus {

	class Renderer {
	private:
		std::unordered_map<const unsigned int, const unsigned int> shaders;



	public:
		Renderer();
		virtual ~Renderer();

		const unsigned int compileShader(const std::string sourceCode, const unsigned int type);

		const std::string shaderSourceFromUrl(const std::string url) const;

		unsigned int buildProgram();


	};

}