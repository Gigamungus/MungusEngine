#pragma once
#include "stdafx.h"

namespace Mungus {
	class Renderer;
	class World;
	class Controller;

	class MUNGUS Application {
	protected:
		std::shared_ptr<Mungus::World> world;
		std::shared_ptr<Mungus::Renderer> renderer;
		std::shared_ptr<Mungus::Controller> controller;

	public:
		Application(void);
		virtual ~Application();
		
		void run(void);


		///////////// client can call these ///////////////
		void inline loadAsset(const std::string& assetPath);
		void inline setBackground(MungusMath::MVec4 color);
		const unsigned long frameCount(void) const;
		/////////////////////////////////////////////////////

		//////// client should override these ///////
		virtual void startup(void);
		virtual void mainLoop(void);
		/////////////////////////////////////////////

		//////////////////// client should IGNORE these ////////////////
		void inline incrementFrameCount(void);
		const unsigned int inline createEntity(const std::string& name);
		void renderActors(void);
		////////////////////////////////////////////////////////////////
		///////////////// good luck with your project //////////////////
	};

	// must be created by client
	Application* createApplication();
}
