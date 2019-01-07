#include "stdafx.h"
#include "Asset.h"


const std::unordered_map<std::string, int> Mungus::ParseAssetFunctions::paramCodes = {
	{
		{"triangle", MTRIANGLE},
		{"actor", MACTOR}
	}
};
const std::unordered_set<char> Mungus::ParseAssetFunctions::enclosureOpenings{ '(', '[', '{' };
const std::unordered_set<char> Mungus::ParseAssetFunctions::enclosureEndings{ ')', ']', '}' };
const std::unordered_set<char> Mungus::ParseAssetFunctions::nums{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };



Mungus::Asset::Asset(	const std::string& name,
						const std::unordered_map<std::string, const unsigned int>& vertexShaders,
						const std::unordered_map<std::string, const unsigned int>& fragmentShaders) :
	assetName(name),
	primitives(std::make_shared<std::vector<Primitive>>())
{
	std::string source = MungusUtil::removeAllWhiteSpace(
		MungusUtil::getTextFromFile(std::filesystem::current_path().string() + "/../resources/assets/" + name + ".txt"));

	auto itr = source.begin();
	assetType = Mungus::ParseAssetFunctions::paramCodes.at(Mungus::ParseAssetFunctions::getVarName(itr));

	MASSERT(assetType != 0, "trying to parse unsupported primitive type in asset: " << name)

	auto properties = Mungus::ParseAssetFunctions::parseObject(itr);

	// parse vertices
	{
		auto vertexDataBuffers = Mungus::ParseAssetFunctions::parseArray(properties.at("vertices"));
		std::vector<float> vertexDataStream;

		std::unordered_map<std::string, std::string::iterator> vertexData;

		for (auto vertexDataBuffer : vertexDataBuffers) {
			vertexData = Mungus::ParseAssetFunctions::parseObject(vertexDataBuffer);

			vertexDataStream.push_back(Mungus::ParseAssetFunctions::parseFloat(vertexData.at("posx")));
			vertexDataStream.push_back(Mungus::ParseAssetFunctions::parseFloat(vertexData.at("posy")));
			vertexDataStream.push_back(Mungus::ParseAssetFunctions::parseFloat(vertexData.at("posz")));
			vertexDataStream.push_back(Mungus::ParseAssetFunctions::parseFloat(vertexData.at("posw")));
		}

		glGenBuffers(1, &(this->vaoID));
		glBindBuffer(GL_ARRAY_BUFFER, this->vaoID);
		glBufferData(GL_ARRAY_BUFFER, vertexDataStream.size()* sizeof(float), vertexDataStream.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
	}

	// parse primitives
	{
		auto primitiveBuffers = Mungus::ParseAssetFunctions::parseArray(properties.at("primitives"));

		for (auto primitiveBuffer : primitiveBuffers) {
			primitives->push_back(Mungus::ParseAssetFunctions::parsePrimitive(primitiveBuffer));
		}
	}

	// parse shaders
	{
		programID = glCreateProgram();
		glBindAttribLocation(programID, 0, "position");

		auto shaderData = Mungus::ParseAssetFunctions::parseObject(properties.at("shaders"));

		auto vertexShaderBuffers = Mungus::ParseAssetFunctions::parseArray(shaderData.at("vertexShaders"));
		auto fragmentShaderBuffers = Mungus::ParseAssetFunctions::parseArray(shaderData.at("fragmentShaders"));

		for (auto vertexShaderBuffer : vertexShaderBuffers)
			glAttachShader(programID, vertexShaders.at(Mungus::ParseAssetFunctions::parseString(vertexShaderBuffer)));

		for (auto fragmentShaderBuffer : fragmentShaderBuffers)
			glAttachShader(programID, fragmentShaders.at(Mungus::ParseAssetFunctions::parseString(fragmentShaderBuffer)));

		glLinkProgram(programID);

		int programLinked;
		glGetProgramiv(programID, GL_LINK_STATUS, &programLinked);
		if (programLinked != GL_TRUE)
		{
			int log_length = 0;
			char message[1024];
			glGetProgramInfoLog(programID, 1024, &log_length, message);
			MLOG(message)
		}
	}
}



// parsing helper functions

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

std::vector<float> Mungus::ParseAssetFunctions::parseVertex(const std::string::iterator& vertexBuffer) {
	auto vertexDataBuffer = parseObject(vertexBuffer);
	std::vector<float> vertexData;

	vertexData.push_back(Mungus::ParseAssetFunctions::parseFloat(vertexDataBuffer.at("posx")));
	vertexData.push_back(Mungus::ParseAssetFunctions::parseFloat(vertexDataBuffer.at("posy")));
	vertexData.push_back(Mungus::ParseAssetFunctions::parseFloat(vertexDataBuffer.at("posz")));
	vertexData.push_back(Mungus::ParseAssetFunctions::parseFloat(vertexDataBuffer.at("posw")));

	return vertexData;
}

Mungus::Primitive Mungus::ParseAssetFunctions::parsePrimitive(const std::string::iterator& primitiveDataBuffer) {

	unsigned int primitiveType;
	unsigned int ibo;
	MungusMath::MVec3 surfaceNormal;
	MungusMath::MVec4 surfaceColor;

	auto primitiveData = Mungus::ParseAssetFunctions::parseObject(primitiveDataBuffer);

	{
		std::string primitiveTypeString = Mungus::ParseAssetFunctions::parseString(primitiveData.at("primitiveType"));

		if (Mungus::ParseAssetFunctions::paramCodes.find(primitiveTypeString) == Mungus::ParseAssetFunctions::paramCodes.end()) {
			MLOG("trying to parse unsupported primitive type: " << primitiveTypeString)
			primitiveType = 0;
		}
		else
			primitiveType = Mungus::ParseAssetFunctions::paramCodes.at(primitiveTypeString);
	}

	{
		auto vertexIndexBuffers = parseArray(primitiveData.at("vertexIndices"));
		std::vector<unsigned int> indices(vertexIndexBuffers.size());

		for (auto vertexIndexBuffer : vertexIndexBuffers)
			indices.push_back((unsigned int)(Mungus::ParseAssetFunctions::parseInt(vertexIndexBuffer)));
		
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndexBuffers.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	}

	{
		auto surfaceNormalBuffer = parseObject(primitiveData.at("surfaceNormal"));
		surfaceNormal.x = parseFloat(surfaceNormalBuffer.at("dirx"));
		surfaceNormal.y = parseFloat(surfaceNormalBuffer.at("diry"));
		surfaceNormal.z = parseFloat(surfaceNormalBuffer.at("dirz"));
	}

	{
		auto surfaceColorBuffer = parseObject(primitiveData.at("surfaceColor"));
		surfaceColor.x = parseFloat(surfaceColorBuffer.at("r"));
		surfaceColor.y = parseFloat(surfaceColorBuffer.at("g"));
		surfaceColor.z = parseFloat(surfaceColorBuffer.at("b"));
		surfaceColor.w = parseFloat(surfaceColorBuffer.at("a"));
	}

	return Mungus::Primitive{primitiveType, ibo, surfaceNormal, surfaceColor};
}
