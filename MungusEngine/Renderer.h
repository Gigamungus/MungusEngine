#pragma once
#include "stdafx.h"

namespace Mungus {

	class Application;
	class Actor;
	class Camera;
	class Entity;
	class Shader;

	class MUNGUS Renderer {
	private:
		const Application* owner;
		GLFWwindow* window;

		std::unordered_map<std::string, Shader> programs;
		float lastFrameTime;

	public:
		Renderer(const Application* owner);
		~Renderer() {};

		void inline setBackground(MungusMath::MVec4 color);

		GLFWwindow* getWindow() const { return window; }
		const std::unordered_map<std::string, Shader> inline getPrograms(void) const { return programs; }


		void renderActors( const std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>>& entities, const Camera& camera);
		void renderActor(const Mungus::Actor& actor, const MungusMath::MMat4& frameTransformations);
		inline const float getLastFrameTime(void) const { return lastFrameTime; };
		inline void setLastFrameTime(float lastFrameTime) { this->lastFrameTime = lastFrameTime; }

		int getWindowWidth(void) const;
		int getWindowHeight(void) const;
	};

}