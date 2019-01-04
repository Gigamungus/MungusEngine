#pragma once
#include "stdafx.h"
#include "Renderer.h"

namespace Mungus {

	class MUNGUS Application {
	private:
		std::vector<std::string> shaderLocations;
		Renderer renderer;

	public:
		Application(void) {};
		virtual ~Application() {};

		virtual void run();

	};

	// must be created by client
	Application* createApplication();
}
