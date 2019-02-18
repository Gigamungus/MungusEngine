#pragma once
#include "stdafx.h"
#include "Application.h"

extern Mungus::Application* Mungus::createApplication();

int main(int argc, char** argv) {
	
	auto app = Mungus::createApplication();
	app->startup();
	app->run();
	delete app;

	return 0;

}
