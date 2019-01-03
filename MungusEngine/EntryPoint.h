#pragma once
#include "Application.h"

extern Mungus::Application* Mungus::createApplication();

int main(int argc, char** argv) {

	auto app = Mungus::createApplication();
	app->run();
	delete app;

	return 0;

}
