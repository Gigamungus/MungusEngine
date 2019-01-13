#include "stdafx.h"
#include "Application.h"
#include "Renderer.h"
#include "World.h"
#include "Controller.h"
#include "Camera.h"

#include "MungusMath.h"
#include "MungusUtil.h"

//////// client call functions /////////////
void inline Mungus::Application::loadAsset(const std::string& assetPath) {
	world->loadAsset(assetPath, renderer->getVertexShaders(), renderer->getFragmentShaders());
}

void inline Mungus::Application::setBackground(MungusMath::MVec4 color) { renderer->setBackground(color); }

const unsigned long Mungus::Application::frameCount(void) const {
	return world->getFrameCount();
}

const unsigned long Mungus::Application::setEntityPosition(const unsigned long id, float x, float y, float z) {
	return world->setEntityPosition(id, x, y, z);
}

const unsigned long Mungus::Application::scaleEntity(const unsigned long id, float x, float y, float z) {
	return world->scaleEntity(id, x, y, z);
}

const unsigned long Mungus::Application::rotateEntity(const unsigned long id, const MungusMath::MVec3 & axis, float angle) {
	return world->rotateEntity(id, axis, angle);
}

void Mungus::Application::moveCamera(float x, float y, float z) {
	world->moveCamera(x, y, z);
}

void Mungus::Application::rotateCamera(float x, float y, float z, float theta) {
	world->rotateCamera(x, y, z, theta);
}

void Mungus::Application::turnCamera(float angle) {
	world->turnCamera(angle);
}

void Mungus::Application::pitchCamera(float angle) {
	world->pitchCamera(angle);
}

void Mungus::Application::rollCamera(float angle) {
	world->rollCamera(angle);
}

////////////////////////////////////////////



////// client override functions ////////

void Mungus::Application::startup(void) {
	MLOG("client didn't override Mungus' startup method")
}

void Mungus::Application::mainLoop(void) {
	MLOG("client didn't override run method")
}

/////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/////////////// client should ignore everything below here ///////////////////
//////////////////////////////////////////////////////////////////////////////


Mungus::Application::Application(void) : 
	world(std::make_shared<Mungus::World>(this)),
	renderer(std::make_shared<Mungus::Renderer>(this)),
	controller(std::make_shared<Mungus::Controller>(this))
{}

Mungus::Application::~Application() {

}

void Mungus::Application::run(void) {
	while (!glfwWindowShouldClose(renderer->getWindow())) {
		glfwPollEvents();
		mainLoop();
		incrementFrameCount();
		renderActors();
		glfwSwapBuffers(renderer->getWindow());
	}
	glfwDestroyWindow(renderer->getWindow());
	glfwTerminate();
}

void inline Mungus::Application::incrementFrameCount(void) {
	world->incrementFrameCount();
}

inline const unsigned long Mungus::Application::createEntity(const std::string & name) {
	return world->createEntity(name);
}

void Mungus::Application::renderActors(void) {
	renderer->renderActors(world->getActors(), world->getCamera());
}