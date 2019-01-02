#include "Mungus.h"

class SandBoxApp : public Mungus::Application {
public:

	virtual void run() {
		std::cout << "running!";
		std::cin.get();
	}


};

Mungus::Application* Mungus::createApplication() {
	return new SandBoxApp();
}
