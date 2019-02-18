#include "stdafx.h"
#include "Asset.h"
#include "VAO.h"
#include "Shader.h"

Mungus::Asset::Asset(	const std::string& name,
						const std::unordered_map<std::string, Shader>& programs) :
	assetName(name),
	vao(nullptr),
	program(nullptr)
{
	json actorJSON = json::parse(
		MungusUtil::getTextFromFile(std::filesystem::current_path().string() + "/../resources/assets/actors/" + name + ".mungass.txt"));

	program = std::make_shared<Shader>(programs.at(actorJSON["program"].get<std::string>()));
	json vertices = actorJSON["vertices"];
	json primitives = actorJSON["primitives"];

	vao = std::make_shared<VAO>(*program, vertices, primitives);

	hitboxCoords = actorJSON["vertexExtremes"];
}
