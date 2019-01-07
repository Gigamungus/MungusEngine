#pragma once
#include "stdafx.h"


namespace Mungus {
	class Application;
	class Entity;
	class Asset;

	class MUNGUS World {
	private:
		const Application* owner;
		std::unordered_map<std::string, std::shared_ptr<Mungus::Asset>> assets;
		std::unordered_map<std::string, std::shared_ptr<Mungus::Entity>> entities;

	public:
		World(const Application* owner);
		virtual ~World() {};

		void inline loadAsset(	const std::string& title,
								const std::unordered_map<std::string, const unsigned int>& vertexShaders,
								const std::unordered_map<std::string, const unsigned int>& fragmentShaders);
	};

}