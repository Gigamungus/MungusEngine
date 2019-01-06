#pragma once
#include "stdafx.h"
#include "Renderer.h"
#include "World.h"
#include "Controller.h"

namespace Mungus {

	class MUNGUS Application {
	private:
		World world;
		Renderer renderer;
		Controller controller;

	public:
		Application(void) : world(*this), renderer(*this), controller(*this) {};
		virtual ~Application() {};

		virtual void startup(void);
		virtual void run(void);

		void inline loadAsset(const std::string& assetPath) {
			auto start = std::chrono::high_resolution_clock::now();

			// operation to be timed ...
			for (int i = 0; i < 1; i++) {
				world.loadAsset(assetPath);
			}

			auto finish = std::chrono::high_resolution_clock::now();

			std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
		};

	};

	// must be created by client
	Application* createApplication();
}
