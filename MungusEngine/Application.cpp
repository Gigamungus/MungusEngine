#include "stdafx.h"
#include "Application.h"

void Mungus::Application::run(void) {
	while (!glfwWindowShouldClose(renderer.getWindow())) {
		mainLoop();
	}
}

void Mungus::Application::startup(void) {
	MLOG("client didn't override Mungus' startup method")
}

void Mungus::Application::mainLoop(void) {
	MLOG("client didn't override run method")
}

