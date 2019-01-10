#include "stdafx.h"
#include "World.h"
#include "Application.h"
#include "Entity.h"
#include "Camera.h"
#include "Actor.h"
#include "Asset.h"

Mungus::World::World(const Application* owner) : owner(owner), frameCount(0), actorCount(0), camera(std::make_shared<Camera>()) {};

void inline Mungus::World::loadAsset(const std::string& title,
	const std::unordered_map<std::string, const unsigned int>& vertexShaders,
	const std::unordered_map<std::string, const unsigned int>& fragmentShaders) {
	assets[title] = std::make_shared<Mungus::Asset>(title, vertexShaders, fragmentShaders);
}
const unsigned int Mungus::World::createEntity(const std::string & name) {
	if (assets.find(name) != assets.end()) {
		std::shared_ptr<Mungus::Asset> base = assets.at(name);

		switch (base->renderInfo.assetType) {
		case MACTOR:
			actors[++actorCount] = std::make_shared<Mungus::Actor>(Mungus::Actor(*base, actorCount));
			break;
		default:
			MLOG("trying to create entity of unknown type: " << name)
				return 0;
		}
		return actorCount;
	}
	return 0;
}

inline const Mungus::Camera Mungus::World::getCamera(void) const {
	return *camera;
}
