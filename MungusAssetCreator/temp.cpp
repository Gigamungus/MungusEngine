#include "Mungus.h"

class MungusAssetCreator : public Mungus::Application {
public:
	virtual void startup(void) override {
		loadAsset("triangle.mungass");
	}

	virtual void mainLoop(void) override {
		std::cout << "working for now...\n";
	}

};

Mungus::Application* Mungus::createApplication() {
	return new MungusAssetCreator();
}  
  