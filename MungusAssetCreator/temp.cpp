#include "Mungus.h"
#define CUBE "cube.mungass"

std::vector<unsigned int> entities = std::vector<unsigned int>();

class MungusAssetCreator : public Mungus::Application {
public:
	virtual void startup(void) override {
		setRPGBindings();
		loadAsset("cube.mungass");
		setCameraMovementSpeed(10);
		setCameraRotationSpeed(180);
	}

	virtual void mainLoop(void) override {
		setBackground(MungusMath::MVec4{ 0.45f, 0.55f, 0.60f, 1.00f });

		int i = frameCount();
		
		unsigned int newEntity = createEntity(CUBE);
		setEntityPosition(newEntity, ((2 * (i % 10)) + (25 * (i / 100))) % 250, 0.0, (2 * ((i / 10)) % 20) + (int)(25 * (i / 1000)));
		entities.push_back(newEntity);
		
		/*for (auto entity : entities) {
			if (entity % 3 == 0) {
				turnEntity(entity, entity);
			}
			if (entity % 3 == 1)
				pitchEntity(entity, entity);

			if (entity % 3 == 2)
				rollEntity(entity, entity);
		}*/
	}

};

Mungus::Application* Mungus::createApplication() {
	return new MungusAssetCreator();
}  
  