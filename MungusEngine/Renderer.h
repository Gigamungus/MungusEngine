#pragma once
#include "stdafx.h"

namespace Mungus {

	class Application;

	class MUNGUS Renderer {
	private:
		const Application& owner;

		std::unordered_map<std::string, const unsigned int> vertexShaders;
		std::unordered_map<std::string, const unsigned int> fragmentShaders;
		GLFWwindow* window;



		void glfwStartup(GLFWwindow*& win);
		void glewStartup(void);

	public:
		Renderer(const Application& owner) : owner(owner) {
			glfwStartup(window);
			glewStartup();
			compileShaders();
		};

		~Renderer() {};

		void compileShaders(void);

		GLFWwindow* getWindow() const { return window; }

	};

}