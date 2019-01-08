#include "Mungus.h"
#define TRIANGLE "triangle.mungass"

class MungusAssetCreator : public Mungus::Application {
public:
	virtual void startup(void) override {
		loadAsset(TRIANGLE);
		loadAsset("triangle2.mungass");
	}

	virtual void mainLoop(void) override {
		setBackground(MungusMath::MVec4{ 0.45f, 0.55f, 0.60f, 1.00f });
		if (frameCount() == 0) {
			const unsigned int firstEntity = createEntity(TRIANGLE);
		}
		if (frameCount() == 100) {
			createEntity("triangle2.mungass");
		}
	
	}

};

Mungus::Application* Mungus::createApplication() {
	return new MungusAssetCreator();
}  
  