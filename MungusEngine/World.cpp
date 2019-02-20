#include "stdafx.h"
#include "World.h"
#include "Application.h"
#include "Camera.h"
#include "Actor.h"
#include "Asset.h"
#include "AABBTree.h"
#include "Shader.h"

Mungus::World::World(const Application* owner) :
	owner(owner),
	frameCount(0),
	camera(std::make_shared<Camera>()),
	actorsTree(std::make_shared<Mungus::AABBTree<Actor>>())
{};

void inline Mungus::World::loadActor(const std::string& title,
	const std::unordered_map<std::string, Shader>& programs) {
	assets[title] = std::make_shared<Mungus::Asset>(title, programs);
}

inline const std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>> Mungus::World::getActors(void) const {
	return actorsTree->getActors();
}

const unsigned long Mungus::World::createActor(const std::string & name, const MungusMath::MVec3 & initialPosition) {
	if (assets.find(name) != assets.end()) {
		std::shared_ptr<Mungus::Asset> base = assets.at(name);
		std::shared_ptr<Mungus::Actor> newActor = std::make_shared<Mungus::Actor>(*base);
		newActor->setPosition(initialPosition);

		return actorsTree->insert(newActor);
	}
	return 0;
}

const unsigned long Mungus::World::setEntityPosition(const unsigned long id, const MungusMath::MVec3& position) {
	actorsTree->setActorPosition(id, position);
	
	return id;
}

const unsigned long Mungus::World::scaleEntity(const unsigned long id, const MungusMath::MVec3& scale) {
	actorsTree->scaleActor(id, scale);
	
	return id;
}

const unsigned long Mungus::World::rotateEntity(const unsigned long id, const MungusMath::MVec3 & axis, float angle) {
	actorsTree->rotateActor(id, axis, angle);
	
	return id;
}

const unsigned long Mungus::World::turnEntity(const unsigned long id, float angle) {
	actorsTree->turnActor(id, angle);
	return id;
}

const unsigned long Mungus::World::pitchEntity(const unsigned long id, float angle) {
	actorsTree->pitchActor(id, angle);
	return id;
}

const unsigned long Mungus::World::rollEntity(const unsigned long id, float angle) {
	actorsTree->rollActor(id, angle);
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

inline Mungus::Camera& Mungus::World::getCamera(void) {
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

MungusMath::Line Mungus::World::getRayFromCursorLocation(const CursorLocation & cursorLocation, float windowWidth, float windowHeight) const {
	return camera->getRayFromCursorLocation(cursorLocation, windowWidth, windowHeight);
}

unsigned long Mungus::World::findFirstIntersecting(const MungusMath::Line & line) {
	return actorsTree->findFirstIntersecting(line);
}
