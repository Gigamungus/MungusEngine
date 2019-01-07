#include "stdafx.h"
#include "Entity.h"

const std::unordered_map<std::string, int> Mungus::ParseAssetFunctions::paramCodes = {
	{
		{"triangle", MTRIANGLE},
		{"actor", MACTOR}
	}
};
const std::unordered_set<char> Mungus::ParseAssetFunctions::enclosureOpenings{ '(', '[', '{' };
const std::unordered_set<char> Mungus::ParseAssetFunctions::enclosureEndings{ ')', ']', '}' };
const std::unordered_set<char> Mungus::ParseAssetFunctions::nums{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };

std::string Mungus::ParseAssetFunctions::getVarName(std::string::iterator& sourceItr) {
	std::stringstream stream;

	// skip opening quote
	sourceItr++;

	// while there is data left to be read
	while (*sourceItr != '"') {
		stream << *sourceItr;
		sourceItr++;
	}

	// skip closing quote and colon
	sourceItr += 2;

	return stream.str();
}

std::unordered_map<std::string, std::string::iterator> Mungus::ParseAssetFunctions::parseObject(const std::string::iterator& sourceItr) {
	std::string::iterator itr(sourceItr);

	std::stack<char> enclosures;

	std::unordered_map<std::string, std::string::iterator> parameters;
	std::string name;
	std::string::iterator nextParam;

	enclosures.push(*itr);
	itr++;

	while (!enclosures.empty()) {
		if (enclosures.size() == 1 && *itr == '"') {
			name = Mungus::ParseAssetFunctions::getVarName(itr);
			parameters[name] = std::string::iterator(itr);
		}

		if (Mungus::ParseAssetFunctions::enclosureOpenings.find(*itr) != Mungus::ParseAssetFunctions::enclosureOpenings.end())
			enclosures.push(*itr);

		else if (Mungus::ParseAssetFunctions::enclosureEndings.find(*itr) != Mungus::ParseAssetFunctions::enclosureEndings.end() && !enclosures.empty())
			enclosures.pop();

		itr++;
	}

	return parameters;
}

std::vector<std::string::iterator> Mungus::ParseAssetFunctions::parseArray(const std::string::iterator& sourceItr) {
	std::string::iterator itr(sourceItr);

	std::stack<char> enclosures;

	std::vector<std::string::iterator> indexedLocations;

	enclosures.push(*itr);
	itr++;

	if (*itr != ']')
		indexedLocations.push_back(std::string::iterator(itr));

	while (!enclosures.empty()) {
		if (Mungus::ParseAssetFunctions::enclosureOpenings.find(*itr) != Mungus::ParseAssetFunctions::enclosureOpenings.end())
			enclosures.push(*itr);

		else if (Mungus::ParseAssetFunctions::enclosureEndings.find(*itr) != Mungus::ParseAssetFunctions::enclosureEndings.end() && !enclosures.empty())
			enclosures.pop();

		if (enclosures.size() == 1 && *itr == ',')
			indexedLocations.push_back(std::string::iterator(itr + 1));

		itr++;
	}

	return indexedLocations;
}

float Mungus::ParseAssetFunctions::parseFloat(const std::string::iterator& position) {
	std::stringstream stream;
	std::string::iterator itr(position);

	while (Mungus::ParseAssetFunctions::nums.find(*itr) != Mungus::ParseAssetFunctions::nums.end()) {
		stream << *itr;
		itr++;
	}

	return std::stof(stream.str());
}

int Mungus::ParseAssetFunctions::parseInt(const std::string::iterator& position) {
	std::stringstream stream;
	std::string::iterator itr(position);

	while (Mungus::ParseAssetFunctions::nums.find(*itr) != Mungus::ParseAssetFunctions::nums.end()) {
		stream << *itr;
		itr++;
	}

	return std::stoi(stream.str());
}

std::string Mungus::ParseAssetFunctions::parseString(const std::string::iterator& position) {
	std::stringstream stream;
	std::string::iterator itr(position);

	while (*itr != ',' && *itr != ']' && *itr != ')' && *itr != '}') {
		stream << *itr;
		itr++;
	}

	return stream.str();
}

MungusMath::MVec4 Mungus::ParseAssetFunctions::parseVertex(const std::string::iterator& vertexDataBuffer) {
	auto vertexData = parseObject(vertexDataBuffer);
	return MungusMath::MVec4{
				parseFloat(vertexData.at("posx")),
				parseFloat(vertexData.at("posy")),
				parseFloat(vertexData.at("posz")),
				parseFloat(vertexData.at("posw")),
	};
}

Mungus::Primitive Mungus::ParseAssetFunctions::parsePrimitive(const std::string::iterator& primitiveDataBuffer) {
	auto primitive = parseObject(primitiveDataBuffer);

	std::string primitiveType = parseString(primitive.at("primitiveType"));

	switch (Mungus::ParseAssetFunctions::paramCodes.at(primitiveType)) {
	case MTRIANGLE: {
		Mungus::Triangle triangle;
		triangle.primType = MTRIANGLE;
		auto primitiveData = parseObject(primitive.at("primitiveData"));

		{
			auto vertexIndices = parseArray(primitiveData.at("vertexIndices"));

			for (auto vertexIndex : vertexIndices) {
				triangle.vertexIndices.push_back(parseInt(vertexIndex));
			}
		}

		{
			auto surfaceNormal = parseObject(primitiveData.at("surfaceNormal"));
			triangle.surfaceNormal.x = parseFloat(surfaceNormal.at("dirx"));
			triangle.surfaceNormal.y = parseFloat(surfaceNormal.at("diry"));
			triangle.surfaceNormal.z = parseFloat(surfaceNormal.at("dirz"));
		}

		{
			auto surfaceColor = parseObject(primitiveData.at("surfaceColor"));
			triangle.surfaceColor.x = parseFloat(surfaceColor.at("r"));
			triangle.surfaceColor.y = parseFloat(surfaceColor.at("g"));
			triangle.surfaceColor.z = parseFloat(surfaceColor.at("b"));
			triangle.surfaceColor.w = parseFloat(surfaceColor.at("a"));
		}

		return triangle;
	}
	default:
		MLOG("trying to compile unknow primitive type" << primitiveType)
			return Mungus::Primitive();
	}
}

