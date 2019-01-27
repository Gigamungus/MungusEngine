#include "Mungus.h"
#define CUBE "cube.mungass"
#include <cstdlib>

std::vector<unsigned int> entities = std::vector<unsigned int>();


class MungusAssetCreator : public Mungus::Application {
public:
	virtual void startup(void) override {
		setNoClipBindings();
		loadAsset("cube.mungass");
		setCameraMovementSpeed(10);
		setCameraRotationSpeed(180);

		for (int i = 0; i < 1000; i++) {
			unsigned int newEntity = createEntity(CUBE);
			setEntityPosition(newEntity, ((2 * (i % 10)) + (25 * (i / 1000))) % 250, (2 * ((i % 1000) / 100)), (2 * ((i / 10)) % 20) + (int)(25 * (i / 10000)));
			entities.push_back(newEntity);
		}
	}

	virtual void mainLoop(void) override {
		setBackground(MungusMath::MVec4{ 0.45f, 0.55f, 0.60f, 1.00f });
		
		std::cout << getPrimarySelection() << "\n";
		
		for (auto entity : entities) {
			if (entity % 3 == 0) {
				turnEntity(entity, 3);
			}
			if (entity % 3 == 1)
				rotateEntity(entity, {1, 0, 0}, 3);

			if (entity % 3 == 2)
				rollEntity(entity, 3);
		}
	}

};

Mungus::Application* Mungus::createApplication() {
	return new MungusAssetCreator();
}  
  