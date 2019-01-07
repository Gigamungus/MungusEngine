#include "stdafx.h"
#include "World.h"
#include "Application.h"
#include "Entity.h"
#include "Asset.h"

Mungus::World::World(const Application* owner) : owner(owner) {};

void inline Mungus::World::loadAsset(const std::string& title,
	const std::unordered_map<std::string, const unsigned int>& vertexShaders,
	const std::unordered_map<std::string, const unsigned int>& fragmentShaders) {
	assets[title] = std::make_shared<Mungus::Asset>(title, vertexShaders, fragmentShaders);
};