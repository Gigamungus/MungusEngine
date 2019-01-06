#include "stdafx.h"
#include "World.h"
#include "Actor.h"

#include "../Resources/MungusLibs/MungusMath.h"
#include "../Resources/MungusLibs/MungusUtil.h"

static std::unordered_map<std::string, int> paramCodes = {
	{
		{"vertices", MVERTICES},
		{"posx", MPOSX},
		{"posy", MPOSY},
		{"posz", MPOSZ},
		{"posw", MPOSW},
		{"primitives", MPRIMITIVES},
		{"primitiveType", MPRIMITIVETYPE},
		{"vertexIndices", MVERTEXINDICES},
		{"surfaceNormal", MSURFACENORMAL},
		{"surfaceColor", MSURFACECOLOR},
		{"shadersToUse", MSHADERSTOUSE},
		{"vertexShaders", MVERTEXSHADERS},
		{"fragmentShaders", MFRAGMENTSHADERS},
		{"triangle", MTRIANGLE},
		{"actor", MACTOR}
	}
};

// get the name of a variable, iterator should start at the first quote, and will end after the colon
std::string getVarName(std::string::iterator& sourceItr);

// break a general buffered collection of data into a tangible collection of iterators at each element
std::unordered_map<std::string, std::string::iterator> parseObject(const std::string::iterator& itr);
std::vector<std::string::iterator> parseArray(const std::string::iterator& itr);

// get integral values from buffer locations
float parseFloat(const std::string::iterator& position);
int parseInt(const std::string::iterator& position);
std::string parseString(const std::string::iterator& position);

// parse more specific collection types into a relevant tangible container
Mungus::MVec4 parseVertex(const std::string::iterator& itr);
Mungus::Primitive parsePrimitive(const std::string::iterator& primitiveDataBuffer);


void Mungus::World::loadAsset(const std::string& assetPath) {
	std::string assetSource = MungusUtil::getTextFromFile(std::filesystem::current_path().string() + "/../resources/assets/" + assetPath + ".txt");
	entities.push_back(createEntityFromSourceString(assetPath, assetSource));
}

std::shared_ptr<Mungus::Entity> Mungus::World::createEntityFromSourceString(const std::string & sourcePath, const std::string & source) {

	std::string sourceText = MungusUtil::removeAllWhiteSpace(source);

	auto itr = sourceText.begin();
	auto end = sourceText.end();

	std::string entityType = getVarName(itr);

	///////////////////////////////////////////////////////////////////
	////////////                                           ////////////
	////////////    update asset layout by editing here    ////////////
	////////////                                           ////////////
	///////////////////////////////////////////////////////////////////

	switch (paramCodes.at(entityType)) {
	case MACTOR: {
		std::shared_ptr<Mungus::Actor> actor = std::make_shared<Mungus::Actor>(sourcePath, MACTOR);

		auto properties = parseObject(itr);

		{
			auto vertices = parseArray(properties.at("vertices"));
			for (auto vertexDataBuffer : vertices)
				actor->addVertex(parseVertex(vertexDataBuffer));
		}

		{
			auto primitives = parseArray(properties.at("primitives"));
			for (auto primitiveBuffer : primitives) {
				actor->addPrimitive(parsePrimitive(primitiveBuffer));
			}
		}
		
		{
			auto shaders = parseObject(properties.at("shaders"));

			auto vertexShaders = parseArray(shaders.at("vertexShaders"));
			auto fragmentShaders = parseArray(shaders.at("fragmentShaders"));

			for (auto vertexShader : vertexShaders) {
				actor->addVertexShader(parseString(vertexShader));
			}

			for (auto fragmentShader : fragmentShaders) {
				actor->addFragmentShader(parseString(fragmentShader));
			}
		}

		return actor;
	}

	default:
		MLOG("trying to load unsupported asset type: " << entityType);
		return nullptr;
	}

	///////////////////////////////////////////////////////////////////////
	//////////////                                           //////////////
	//////////////    update asset layout by editing here    //////////////
	//////////////                                           //////////////
	///////////////////////////////////////////////////////////////////////
}

// parsing support functions
static std::unordered_set<char> enclosureOpenings{ '(', '[', '{' };
static std::unordered_set<char> enclosureEndings{ ')', ']', '}' };


std::string getVarName(std::string::iterator& sourceItr) {
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

std::unordered_map<std::string, std::string::iterator> parseObject(const std::string::iterator& sourceItr) {
	std::string::iterator itr(sourceItr);

	std::stack<char> enclosures;

	std::unordered_map<std::string, std::string::iterator> parameters;
	std::string name;
	std::string::iterator nextParam;

	enclosures.push(*itr);
	itr++;

	while (!enclosures.empty()) {
		if (enclosures.size() == 1 && *itr == '"') {
			name = getVarName(itr);
			parameters[name] = std::string::iterator(itr);
		}

		if (enclosureOpenings.find(*itr) != enclosureOpenings.end())
			enclosures.push(*itr);

		else if (enclosureEndings.find(*itr) != enclosureEndings.end() && !enclosures.empty())
			enclosures.pop();

		itr++;
	}

	return parameters;
}

std::vector<std::string::iterator> parseArray(const std::string::iterator& sourceItr) {
	std::string::iterator itr(sourceItr);

	std::stack<char> enclosures;
	
	std::vector<std::string::iterator> indexedLocations;

	enclosures.push(*itr);
	itr++;

	if (*itr != ']')
		indexedLocations.push_back(std::string::iterator(itr));

	while (!enclosures.empty()) {
		if (enclosureOpenings.find(*itr) != enclosureOpenings.end())
			enclosures.push(*itr);

		else if (enclosureEndings.find(*itr) != enclosureEndings.end() && !enclosures.empty())
			enclosures.pop();

		if (enclosures.size() == 1 && *itr == ',')
			indexedLocations.push_back(std::string::iterator(itr + 1));

		itr++;
	}

	return indexedLocations;
}

float parseFloat(const std::string::iterator& position) {
	return std::stof(&(*(position)));
}

int parseInt(const std::string::iterator& position) {
	return std::stoi(&(*(position)));
}

std::string parseString(const std::string::iterator& position) {
	std::stringstream stream;
	std::string::iterator itr(position);

	while (*itr != ',' && *itr != ']' && *itr != ')' && *itr != '}') {
		stream << *itr;
		itr++;
	}

	return stream.str();
}

Mungus::MVec4 parseVertex(const std::string::iterator& vertexDataBuffer) {
	auto vertexData = parseObject(vertexDataBuffer);
	return Mungus::MVec4{
				parseFloat(vertexData.at("posx")),
				parseFloat(vertexData.at("posy")),
				parseFloat(vertexData.at("posz")),
				parseFloat(vertexData.at("posw")),
	};
}

Mungus::Primitive parsePrimitive(const std::string::iterator& primitiveDataBuffer) {
	auto primitive = parseObject(primitiveDataBuffer);

	std::string primitiveType = parseString(primitive.at("primitiveType"));

	switch (paramCodes.at(primitiveType)) {
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
