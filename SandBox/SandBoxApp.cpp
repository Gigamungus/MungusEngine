#include "Mungus.h"

class SandBoxApp : public Mungus::Application {
public:
};

Mungus::Application* Mungus::createApplication() {
	return new SandBoxApp();
}
 