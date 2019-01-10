#pragma once
#include "stdafx.h"


namespace Mungus {
	class Application;
	class Actor;
	class Asset;
	class Camera;

	class MUNGUS World {
	private:
		const Application* owner;
		unsigned long frameCount;
		unsigned long actorCount;
		std::unordered_map<std::string, std::shared_ptr<Mungus::Asset>> assets;
		std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>> actors;
		std::shared_ptr<Camera> camera;

	public:
		World(const Application* owner);
		virtual ~World() {};

		void inline loadAsset(	const std::string& title,
								const std::unordered_map<std::string, const unsigned int>& vertexShaders,
								const std::unordered_map<std::string, const unsigned int>& fragmentShaders);

		const inline unsigned long getFrameCount(void) const { return frameCount; }
		void inline incrementFrameCount(void) { frameCount++; }
		const std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>> inline getActors(void) const { return actors; }
		const unsigned int createEntity(const std::string& name);
		const Camera inline getCamera(void) const;
	};


}