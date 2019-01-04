#include "Mungus.h"

class MungusAssetCreator : public Mungus::Application {
public:
};

Mungus::Application* Mungus::createApplication() {
	return new MungusAssetCreator();
}  
  