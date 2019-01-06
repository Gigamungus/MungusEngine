#pragma once
#include "stdafx.h"
#include "Entity.h"


namespace Mungus {

	class Application;

	class MUNGUS World {
	private:
		const Application& owner;
		std::vector<std::shared_ptr<Mungus::Entity>> entities;

	public:
		World(const Application& owner) : owner(owner) {};
		virtual ~World() {};

		void loadAsset(const std::string& title);
		std::shared_ptr<Entity> createEntityFromSourceString(const std::string& sourcePath, const std::string& sourceText);
	};

}