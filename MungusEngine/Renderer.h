#pragma once
#include "stdafx.h"

namespace Mungus {

	class Application;
	class Actor;


	class MUNGUS Renderer {
	private:
		const Application* owner;
		GLFWwindow* window;

		std::unordered_map<std::string, const unsigned int> vertexShaders;
		std::unordered_map<std::string, const unsigned int> fragmentShaders;

	public:
		Renderer(const Application* owner);
		~Renderer() {};

		void renderActor(Mungus::Actor actor);
		void inline setBackground(MungusMath::MVec4 color);
		

		GLFWwindow* getWindow() const { return window; }
		const std::unordered_map<std::string, const unsigned int> inline getVertexShaders(void) const { return vertexShaders; }
		const std::unordered_map<std::string, const unsigned int> inline getFragmentShaders(void) const { return fragmentShaders; }
	};

}