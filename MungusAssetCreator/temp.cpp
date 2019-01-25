#include "Mungus.h"
#define CUBE "cube.mungass"
#include <cstdlib>

std::vector<unsigned int> entities = std::vector<unsigned int>();

int i = 0;

class MungusAssetCreator : public Mungus::Application {
public:
	virtual void startup(void) override {
		setNoClipBindings();
		loadAsset("cube.mungass");
		setCameraMovementSpeed(10);
		setCameraRotationSpeed(180);
	}

	virtual void mainLoop(void) override {
		setBackground(MungusMath::MVec4{ 0.45f, 0.55f, 0.60f, 1.00f });
		
		float f = frameTime() * 360;
		
		for (int j = 0; j < f; j++) {
			unsigned int newEntity = createEntity(CUBE);
			setEntityPosition(newEntity, ((2 * (i % 10)) + (25 * (i / 1000))) % 250, (2 * ((i % 1000) / 100)), (2 * ((i / 10)) % 20) + (int)(25 * (i / 10000)));
			/*setEntityPosition(newEntity, ((float)rand() / (float)RAND_MAX) * 100, ((float)rand() / (float)RAND_MAX) * 100, ((float)rand() / (float)RAND_MAX) * 100);
			entities.push_back(newEntity);*/
			i++;
		}
		
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
  