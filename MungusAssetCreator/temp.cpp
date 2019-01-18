#include "Mungus.h"
#define CUBE "cube.mungass"


class MungusAssetCreator : public Mungus::Application {
public:
	virtual void startup(void) override {
		setRPGBindings();
		loadAsset(CUBE);
		setCameraMovementSpeed(10);
		setCameraRotationSpeed(180);
	}

	virtual void mainLoop(void) override {
		setBackground(MungusMath::MVec4{ 0.45f, 0.55f, 0.60f, 1.00f });

		int i = frameCount();

		unsigned int newEntity = createEntity(CUBE);
		setEntityPosition(newEntity, ((2 * (i % 10)) + (25 * (i / 100))) % 250, 0.0, (2 * ((i / 10)) % 20) + (int)(25 * (i / 1000)));
	}

};

Mungus::Application* Mungus::createApplication() {
	return new MungusAssetCreator();
}  
  