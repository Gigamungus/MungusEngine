#include "stdafx.h"
#include "Actor.h"

Mungus::Actor::Actor(const std::string& assetPath, const unsigned int entityType, std::string::iterator& itr) : Mungus::Entity(assetPath, entityType) {
	auto properties = Mungus::ParseAssetFunctions::parseObject(itr);

	{
		auto vertices = Mungus::ParseAssetFunctions::parseArray(properties.at("vertices"));
		for (auto vertexDataBuffer : vertices)
			addVertex(Mungus::ParseAssetFunctions::parseVertex(vertexDataBuffer));
	}

	{
		auto primitives = Mungus::ParseAssetFunctions::parseArray(properties.at("primitives"));
		for (auto primitiveBuffer : primitives) {
			addPrimitive(Mungus::ParseAssetFunctions::parsePrimitive(primitiveBuffer));
		}
	}

	{
		auto shaders = Mungus::ParseAssetFunctions::parseObject(properties.at("shaders"));

		auto vertexShaders = Mungus::ParseAssetFunctions::parseArray(shaders.at("vertexShaders"));
		auto fragmentShaders = Mungus::ParseAssetFunctions::parseArray(shaders.at("fragmentShaders"));

		for (auto vertexShader : vertexShaders) {
			addVertexShader(Mungus::ParseAssetFunctions::parseString(vertexShader));
		}

		for (auto fragmentShader : fragmentShaders) {
			addFragmentShader(Mungus::ParseAssetFunctions::parseString(fragmentShader));
		}
	}
}
