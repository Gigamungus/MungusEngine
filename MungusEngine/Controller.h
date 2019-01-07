#pragma once
#include "stdafx.h"

namespace Mungus {

	class Application;

	class MUNGUS Controller {
	private:
		const Application* owner;

	public:
		Controller(const Application* owner) : owner(owner) {};
		virtual ~Controller() {};

	};

}
