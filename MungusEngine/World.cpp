#include "stdafx.h"
#include "World.h"
#include "Application.h"
#include "Entity.h"
#include "Actor.h"
#include "Asset.h"

Mungus::World::World(const Application* owner) : owner(owner), frameCount(0), entityCount(0) {};

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
			entities[++entityCount] = std::make_shared<Mungus::Actor>(Mungus::Actor(*base, entityCount));
			break;
		default:
			MLOG("trying to create entity of unknown type: " << name)
				return 0;
		}
		return entityCount;
	}
	return 0;
}
