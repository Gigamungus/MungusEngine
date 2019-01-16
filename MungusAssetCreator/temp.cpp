#include "Mungus.h"
#define CUBE "cube.mungass"

unsigned long firstEntity;

class MungusAssetCreator : public Mungus::Application {
public:
	virtual void startup(void) override {
		setDefaultBindings();
		loadAsset(CUBE);
	}

	virtual void mainLoop(void) override {
		setBackground(MungusMath::MVec4{ 0.45f, 0.55f, 0.60f, 1.00f });
		if (frameCount() == 0) {
			firstEntity = createEntity(CUBE);
			setEntityPosition(firstEntity, 0.0, 0.0, 0.0);
			moveCamera({ 0.0, 2.0, -2.0 });
			pitchCamera(-35);

			int width = 10;

			for (int j = -width; j <= width; j += 2) {
				for (int i = -width; i <= width; i += 2) {
					unsigned int newEntity = createEntity(CUBE);
					setEntityPosition(newEntity, (float)i, 0.0, (float)j);
				}
			}
		}
/*
		turnCamera(-1);
		setCameraPosition(10.0f * sin((float)(frameCount()) * ((3.1415926535897932384626433f) / 180.0f)), 5.0f, 10.0f * (-cos((float)(frameCount()) * (6.284f / 360.0f))));
		*/
	}

};

Mungus::Application* Mungus::createApplication() {
	return new MungusAssetCreator();
}  
  