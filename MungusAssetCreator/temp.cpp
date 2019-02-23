#include "Mungus.h"
#include <cstdlib>

#define CUBE "cube"
//#define DEBUGMODE

std::vector<unsigned int> entities = std::vector<unsigned int>();


class MungusAssetCreator : public Mungus::Application {
public:
	virtual void startup(void) override {
		setNoClipBindings();
#ifdef DEBUGMODE
		enableDebug();
#endif
		loadActor(CUBE);

		//editAsset(CUBE);

		

		setCameraMovementSpeed(10);
		setCameraRotationSpeed(180);
		enableWireFrameMode();

		for (int i = 0; i < 1; i++) {
			if (i % 100 == 0) {
				std::cout << i << "\n";
			}
			unsigned int newEntity = createActor(CUBE);
			//setEntityPosition(newEntity, ((2 * (i % 10)) + (25 * (i / 1000))) % 250, (2 * ((i % 1000) / 100)), 2 + (2 * ((i / 10)) % 20) + (int)(25 * (i / 10000)));
			entities.push_back(newEntity);
		}
	}

	virtual void mainLoop(void) override {
		setBackground(MungusMath::MVec4{ 0.45f, 0.55f, 0.60f, 1.00f });

		//testChangeVertexCoord("cube", 0, MungusMath::MVec3(0, 0, (float)frameCount() / (-100.0)));

		//std::cout << getPrimarySelection() << "\n";
		/*
		for (auto entity : entities) {
			if (entity % 3 == 0) {
				turnEntity(entity, 3);
			}
			if (entity % 3 == 1)
				rotateEntity(entity, {1, 0, 0}, 3);

			if (entity % 3 == 2)
				rollEntity(entity, 3);
		}*/
	}

};

Mungus::Application* Mungus::createApplication() {
	return new MungusAssetCreator();
}  
  