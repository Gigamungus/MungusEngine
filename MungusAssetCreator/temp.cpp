#include "Mungus.h"

class MungusAssetCreator : public Mungus::Application {
public:
	virtual void startup(void) override {
		loadAsset("triangle.mungass");
		
	}

	virtual void mainLoop(void) override {
		setBackground(MungusMath::MVec4{ 0.45f, 0.55f, 0.60f, 1.00f });
	}

};

Mungus::Application* Mungus::createApplication() {
	return new MungusAssetCreator();
}  
  