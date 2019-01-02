#pragma once
#include "Core.h"

namespace Mungus {

	class MUNGUS Application {
	public:
		Application();
		virtual ~Application();

		virtual void run() {
			while (true);
		}
	};


	// must be created by client
	Application* createApplication();
}

