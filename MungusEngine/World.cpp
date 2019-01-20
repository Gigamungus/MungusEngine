#include "stdafx.h"
#include "World.h"
#include "Application.h"
#include "Camera.h"
#include "Actor.h"
#include "Asset.h"
#include "AABBTree.h"

Mungus::World::World(const Application* owner) :
	owner(owner),
	frameCount(0),
	actorCount(0),
	camera(std::make_shared<Camera>()),
	actorsTree(std::make_shared<AABBTree>(&actors))
{};

void inline Mungus::World::loadAsset(const std::string& title,
	const std::unordered_map<std::string, const unsigned int>& vertexShaders,
	const std::unordered_map<std::string, const unsigned int>& fragmentShaders) {
	assets[title] = std::make_shared<Mungus::Asset>(title, vertexShaders, fragmentShaders);
}

void Mungus::World::buildActorTree(void) {
	actorsTree->buildTree();
}

const unsigned long Mungus::World::createEntity(const std::string & name) {
	if (assets.find(name) != assets.end()) {
		std::shared_ptr<Mungus::Asset> base = assets.at(name);

		switch (base->renderInfo.assetType) {
		case MACTOR:
			actors[actorCount] = std::make_shared<Mungus::Actor>(Mungus::Actor(*base, ++actorCount));
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

const unsigned long Mungus::World::turnEntity(const unsigned long id, float angle) {
	actors.at(id)->turn(angle);
	return id;
}

const unsigned long Mungus::World::pitchEntity(const unsigned long id, float angle) {
	actors.at(id)->pitch(angle);
	return id;
}

const unsigned long Mungus::World::rollEntity(const unsigned long id, float angle) {
	actors.at(id)->roll(angle);
	return id;
}

const MungusMath::MVec3 Mungus::World::getCameraPosition(void) const {
	return camera->getPosition();
}

void Mungus::World::setCameraPosition(float x, float y, float z) {
	camera->setPosition(MungusMath::MVec3{ x, y, z });
}

void Mungus::World::moveCamera(const MungusMath::MVec3& moveBy) {
	camera->setPosition(camera->getPosition() + moveBy);
}

const MungusMath::MVec3 Mungus::World::getCameraForward(void) const {
	return camera->forward();
}

const MungusMath::MVec3 Mungus::World::getCameraUp(void) const {
	return camera->up();
}

const MungusMath::MVec3 Mungus::World::getCameraRight(void) const {
	return camera->right();
}

const MungusMath::MVec3 Mungus::World::getCameraPlanarForward(void) const {
	return camera->planarForward();
}

const MungusMath::MVec3 Mungus::World::getCameraPlanarUp(void) const {
	return camera->planarUp();
}

const MungusMath::MVec3 Mungus::World::getCameraPlanarRight(void) const {
	return camera->planarRight();
}

void Mungus::World::setCameraStrafingStatus(int setting) {
	camera->strafing = setting;
}

void Mungus::World::setCameraAscendingStatus(int setting) {
	camera->ascending = setting;
}

void Mungus::World::setCameraAdvancingStatus(int setting) {
	camera->advancing = setting;
}

void Mungus::World::setCameraTurningStatus(int setting) {
	camera->turning = setting;
}

void Mungus::World::setCameraPitchingStatus(int setting) {
	camera->pitching = setting;
}

void Mungus::World::setCameraRollingStatus(int setting) {
	camera->rolling = setting;
}

const float Mungus::World::getCameraRotationSpeed() const {
	return camera->getRotationSpeed();
}

void Mungus::World::setCameraRotationSpeed(float speed) {
	camera->setRotationSpeed(speed);
}

float Mungus::World::getCameraMovementSpeed() const {
	return camera->getMovementSpeed();
}

void Mungus::World::setCameraMovementSpeed(float speed) {
	camera->setMovementSpeed(speed);
}

void Mungus::World::rotateCamera(const MungusMath::MVec3& axis, float theta) {
	camera->rotate(axis, theta);
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
