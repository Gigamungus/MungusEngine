#pragma once
#include "stdafx.h"

namespace Mungus {

	class Application;
	class Actor;
	class Camera;
	class Entity;


	class MUNGUS Renderer {
	private:
		const Application* owner;
		GLFWwindow* window;

		std::unordered_map<std::string, const unsigned int> vertexShaders;
		std::unordered_map<std::string, const unsigned int> fragmentShaders;
		float lastFrameTime;

	public:
		Renderer(const Application* owner);
		~Renderer() {};

		void inline setBackground(MungusMath::MVec4 color);
		

		GLFWwindow* getWindow() const { return window; }
		const std::unordered_map<std::string, const unsigned int> inline getVertexShaders(void) const { return vertexShaders; }
		const std::unordered_map<std::string, const unsigned int> inline getFragmentShaders(void) const { return fragmentShaders; }

		void renderActors( const std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>>& entities, const Camera& camera);
		void renderActor(const Mungus::Actor& actor, const MungusMath::MMat4& frameTransformations);
		inline const float getLastFrameTime(void) const { return lastFrameTime; };
		inline void setLastFrameTime(float lastFrameTime) { this->lastFrameTime = lastFrameTime; }
	};

}