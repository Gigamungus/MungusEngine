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
		loadActor("cube");
		setCameraMovementSpeed(10);
		setCameraRotationSpeed(180);

		MungusMath::MVec3 direction = MungusMath::MVec3::normalize({ 23, -25, 1 });
		MungusMath::MVec3 position = MungusMath::MVec3({ 0.25, 0.25, 0 }) + (direction * 1000.0f);

		enableWireFrameMode();

		for (int i = 0; i < 1; i++) {
			if (i % 100 == 0) {
				std::cout << i << "\n";
			}
			unsigned int newEntity = createActor(CUBE, MungusMath::MVec3(((2 * (i % 10)) + (25 * (i / 1000))) % 250, (2 * ((i % 1000) / 100)), (2 * ((i / 10)) % 20) + (int)(25 * (i / 10000))));
			//setEntityPosition(newEntity, /*((2 * (i % 10)) + (25 * (i / 1000))) % 250, (2 * ((i % 1000) / 100)), (2 * ((i / 10)) % 20) + (int)(25 * (i / 10000))*/);
			//setEntityPosition(newEntity, 0, 0, i * 2);
			entities.push_back(newEntity);
		}
	}

	virtual void mainLoop(void) override {
		setBackground(MungusMath::MVec4{ 0.45f, 0.55f, 0.60f, 1.00f });

		testChangeVertexCoord("cube", 0, MungusMath::MVec3(-0.01, 0, 0));

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
  