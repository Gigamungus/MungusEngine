#pragma once
#include "stdafx.h"

namespace Mungus {

	class Application;

	class MUNGUS Renderer {
	private:
		const Application& owner;
		GLFWwindow* window;

		std::unordered_map<std::string, const unsigned int> vertexShaders;
		std::unordered_map<std::string, const unsigned int> fragmentShaders;

	public:
		Renderer(const Application& owner);
		~Renderer() {};



		GLFWwindow* getWindow() const { return window; }

	};

}