#include "Mungus.h"
#define TRIANGLE "triangle.mungass"

unsigned long firstEntity;

class MungusAssetCreator : public Mungus::Application {
public:
	virtual void startup(void) override {
		loadAsset(TRIANGLE);
	}

	virtual void mainLoop(void) override {
		setBackground(MungusMath::MVec4{ 0.45f, 0.55f, 0.60f, 1.00f });
		if (frameCount() == 0) {
			firstEntity = createEntity(TRIANGLE);
			setEntityPosition(firstEntity, 0.0, 0.0, -2.0);
			moveCamera(0, 2.0, -10.0);
			turnCamera(180);
		}

		moveCamera(cos(frameCount() / 60.0) / 20.0, -sin(frameCount() / 60.0) / 20.0, 0.0);


		/*
		moveCamera(0, 0, cos(frameCount() / 60));*/
		/*
		if (frameCount() == 100) {
			const unsigned long secondEntity = createEntity(TRIANGLE);
			setEntityPosition(secondEntity, -0.5, -0.5, -0.5);
		}*/

	}

};

Mungus::Application* Mungus::createApplication() {
	return new MungusAssetCreator();
}  
  