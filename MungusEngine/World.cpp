#include "stdafx.h"
#include "World.h"
#include "Application.h"
#include "Camera.h"
#include "Actor.h"
#include "Asset.h"

Mungus::World::World(const Application* owner) : owner(owner), frameCount(0), actorCount(0), camera(std::make_shared<Camera>()) {};

void inline Mungus::World::loadAsset(const std::string& title,
	const std::unordered_map<std::string, const unsigned int>& vertexShaders,
	const std::unordered_map<std::string, const unsigned int>& fragmentShaders) {
	assets[title] = std::make_shared<Mungus::Asset>(title, vertexShaders, fragmentShaders);
}

const unsigned long Mungus::World::createEntity(const std::string & name) {
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

const unsigned long Mungus::World::setEntityPosition(const unsigned long id, float x, float y, float z) {
	actors.at(id)->setPosition(MungusMath::MVec3{ x, y, z });
	
	return id;
}

const unsigned long Mungus::World::scaleEntity(const unsigned long id, float x, float y, float z) {
	actors.at(id)->scaleBy(x, y, z);
	
	return id;
}

const unsigned long Mungus::World::rotateEntity(const unsigned long id, const MungusMath::MVec3 & axis, float angle) {
	actors.at(id)->rotate(axis, angle);
	
	return id;
}

void Mungus::World::setCameraPosition(float x, float y, float z) {
	camera->setPosition(MungusMath::MVec3{ x, y, z });
}

void Mungus::World::moveCamera(float x, float y, float z) {
	camera->setPosition(MungusMath::MVec3{x, y, z} + camera->getPosition());
}

void Mungus::World::rotateCamera(float x, float y, float z, float theta) {
	camera->rotate(MungusMath::MVec3{ x, y, z }, theta);
}

inline const Mungus::Camera Mungus::World::getCamera(void) const {
	return *camera;
}

void Mungus::World::turnCamera(float angle) {
	camera->turn(angle);
}			 
			 
void Mungus::World::pitchCamera(float angle) {
	camera->pitch(angle);
}			 
			 
void Mungus::World::rollCamera(float angle) {
	camera->roll(angle);
}
