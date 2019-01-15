#pragma once
#include "stdafx.h"

namespace Mungus {
	class Renderer;
	class World;
	class Controller;

	class MUNGUS Application {
	private:

	protected:
		std::shared_ptr<Mungus::World> world;
		std::shared_ptr<Mungus::Renderer> renderer;
		std::shared_ptr<Mungus::Controller> controller;

	public:
		Application(void);
		virtual ~Application();
		
		void run(void);


		///////////// client can call these ///////////////
		void setDefaultBindings(void);
		void inline loadAsset(const std::string& assetPath);
		void inline setBackground(MungusMath::MVec4 color);
		const unsigned long frameCount(void) const;
		const unsigned long setEntityPosition(const unsigned long id, float x, float y, float z);
		const unsigned long scaleEntity(const unsigned long id, float x, float y, float z);
		const unsigned long rotateEntity(const unsigned long id, const MungusMath::MVec3& axis, float angle);
		void setCameraPosition(float x, float y, float z);
		void moveCamera(float x, float y, float z);
		void rotateCamera(float x, float y, float z, float theta);
		void turnCamera(float angle);
		void pitchCamera(float angle);
		void rollCamera(float angle);
		/////////////////////////////////////////////////////

		//////// client should override these ///////
		virtual void startup(void);
		virtual void mainLoop(void);
		/////////////////////////////////////////////

		//////////////////// client should IGNORE these ////////////////
		void inline incrementFrameCount(void);
		const unsigned long inline createEntity(const std::string& name);
		void renderActors(void);
		////////////////////////////////////////////////////////////////
		///////////////// good luck with your project //////////////////
	};

	// must be created by client
	Application* createApplication();
}
