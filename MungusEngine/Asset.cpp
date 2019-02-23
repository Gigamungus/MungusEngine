#include "stdafx.h"
#include "Asset.h"
#include "VAO.h"
#include "Shader.h"

Mungus::Asset::Asset(	const std::string& name,
						const std::unordered_map<std::string, Shader>& programs) :
	assetName(name),
	vao(nullptr),
	program(nullptr),
	boundingBoxCoords(std::unordered_map<std::string, std::vector<std::vector<float>>>())
{
	json actorJSON = json::parse(
		MungusUtil::getTextFromFile(std::filesystem::current_path().string() + "/../resources/assets/actors/" + name + ".mungass.txt"));

	program = std::make_shared<Shader>(programs.at(actorJSON["program"].get<std::string>()));
	json vertices = actorJSON["vertices"];
	json primitives = actorJSON["primitives"];

	for (auto& [key, value] : actorJSON["animations"].items()) {
		std::string name = key;
		std::vector<std::vector<float>> points = value["vertexExtremes"];
		boundingBoxCoords.insert(std::make_pair(name, points));
	}

	vao = std::make_shared<VAO>(*program, vertices, primitives);
}

const std::vector<float> Mungus::Asset::getHitboxCoords(const std::string & animation, unsigned int frame) const {
	std::vector<float> coords = boundingBoxCoords.at(animation)[frame];
	float tmp = coords[2];
	coords[2] = -coords[5];
	coords[5] = -tmp;
	return coords;
}

long Mungus::Asset::findIntersectingVertex(const MungusMath::Line & ray) const {
	return vao->findIntersectingVertex(ray);
}

void Mungus::Asset::editVertexCoordinate(long vertexId, const MungusMath::MVec3 & newPosition) {
	vao->moveVertex(vertexId, newPosition);
}
