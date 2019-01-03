#pragma once

#include "pch.h"

#include "Core.h"
#include "Renderer.h"

namespace Mungus {

	class MUNGUS Application {
	private:
		Renderer renderer;

	public:
		Application();
		virtual ~Application();

		virtual void run();

	};

	// must be created by client
	Application* createApplication();
}
