#pragma once
#include "stdafx.h"
#include "Renderer.h"
#include "World.h"
#include "Controller.h"

namespace Mungus {

	class MUNGUS Application {
	protected:
		World world;
		Renderer renderer;
		Controller controller;

	public:
		Application(void) : world(*this), renderer(*this), controller(*this) {}
		virtual ~Application() {}
		
		void run(void);

		void inline loadAsset(const std::string& assetPath) { world.loadAsset(assetPath); }



		//////// client should override these ///////
		virtual void startup(void);
		virtual void mainLoop(void);
		/////////////////////////////////////////////

	};

	// must be created by client
	Application* createApplication();
}
