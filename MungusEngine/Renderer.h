#pragma once
#include "stdafx.h"

namespace Mungus {

	class Renderer {
	private:
		std::unordered_map<std::string, const unsigned int> vertexShaders;
		std::unordered_map<std::string, const unsigned int> fragmentShaders;
		GLFWwindow* window;


		inline std::string getFileName(const std::string& url);
	public:
		Renderer() {};
		Renderer(GLFWwindow* window, std::vector<std::string> urls);
		~Renderer();

		const unsigned int compileShader(const std::string& sourceCode, const unsigned int& type);

		const std::string shaderSourceFromUrl(const std::string url) const;

	};

}