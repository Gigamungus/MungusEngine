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

		void inline loadAsset(const std::string& assetPath);
		void inline setBackground(MungusMath::MVec4 color);


		//////// client should override these ///////
		virtual void startup(void);
		virtual void mainLoop(void);
		/////////////////////////////////////////////

	};

	// must be created by client
	Application* createApplication();
}
