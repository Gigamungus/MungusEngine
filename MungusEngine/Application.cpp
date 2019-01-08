#include "stdafx.h"
#include "Application.h"
#include "Renderer.h"
#include "World.h"
#include "Controller.h"

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
		renderEntities();
		glfwSwapBuffers(renderer->getWindow());
	}
	glfwDestroyWindow(renderer->getWindow());
	glfwTerminate();
}

void inline Mungus::Application::incrementFrameCount(void) {
	world->incrementFrameCount();
}

inline const unsigned int Mungus::Application::createEntity(const std::string & name) {
	return world->createEntity(name);
}

void Mungus::Application::renderEntities(void) {
	renderer->renderEntities(world->getEntities());
}