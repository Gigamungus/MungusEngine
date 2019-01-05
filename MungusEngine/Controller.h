#pragma once
#include "stdafx.h"

namespace Mungus {

	class Application;

	class MUNGUS Controller {
	private:
		Application* owner;

	public:
		Controller(Application* owner) : owner(owner) {};
		virtual ~Controller() {};

	};

}
