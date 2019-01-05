#include "Mungus.h"

class MungusAssetCreator : public Mungus::Application {
public:
	virtual void startup(void) override {
		loadAsset("triangle.mungass");
	}
};

Mungus::Application* Mungus::createApplication() {
	return new MungusAssetCreator();
}  
  