#pragma once
#include "stdafx.h"

namespace Mungus {

	class MUNGUS Renderer {
	private:
		std::unordered_map<std::string, const unsigned int> vertexShaders;
		std::unordered_map<std::string, const unsigned int> fragmentShaders;
		GLFWwindow* window;


		inline std::string getFileName(const std::string& url) const;
	public:
		Renderer(void);
		~Renderer() {};

		void glfwStartup(GLFWwindow** win);
		void glewStartup(void);

		void compileShaders(void);
		const unsigned int compileShader(const std::string sourceCode, const unsigned int& type) const;
		const std::string shaderSourceFromUrl(const std::string url) const;

		GLFWwindow* getWindow() const { return window; }

	};

}