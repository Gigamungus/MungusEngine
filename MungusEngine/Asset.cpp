#include "stdafx.h"
#include "Asset.h"

const std::unordered_map<std::string, int> Mungus::ParseAssetHelpers::paramCodes = {
	{
		{"triangle", MTRIANGLE},
		{"actor", MACTOR}
	}
};
const std::unordered_set<char> Mungus::ParseAssetHelpers::enclosureOpenings{ '(', '[', '{' };
const std::unordered_set<char> Mungus::ParseAssetHelpers::enclosureEndings{ ')', ']', '}' };
const std::unordered_set<char> Mungus::ParseAssetHelpers::nums{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '-' };



Mungus::Asset::Asset(	const std::string& name,
						const std::unordered_map<std::string, const unsigned int>& vertexShaders,
						const std::unordered_map<std::string, const unsigned int>& fragmentShaders) :
	assetName(name)
{
	std::string source = MungusUtil::removeAllWhiteSpace(
		MungusUtil::getTextFromFile(std::filesystem::current_path().string() + "/../resources/assets/" + name + ".txt"));

	auto itr = source.begin();
	renderInfo.assetType = Mungus::ParseAssetHelpers::paramCodes.at(Mungus::ParseAssetHelpers::getVarName(itr));

	MASSERT(renderInfo.assetType != 0, "trying to parse unsupported primitive type in asset: " << name)

	auto properties = Mungus::ParseAssetHelpers::parseObject(itr);

	glGenVertexArrays(1, &(this->renderInfo.VAO));
	glBindVertexArray(this->renderInfo.VAO);

	unsigned int vertexBuffer;
	unsigned int indexBuffer;

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	// parse vertices
	{
		auto vertexDataBuffers = Mungus::ParseAssetHelpers::parseArray(properties.at("vertices"));
		std::vector<float> vertexDataStream;

		std::unordered_map<std::string, std::string::iterator> vertexData;

		for (auto vertexDataBuffer : vertexDataBuffers) {
			vertexData = Mungus::ParseAssetHelpers::parseObject(vertexDataBuffer);

			vertexDataStream.push_back(Mungus::ParseAssetHelpers::parseFloat(vertexData.at("posx")));
			vertexDataStream.push_back(Mungus::ParseAssetHelpers::parseFloat(vertexData.at("posy")));
			vertexDataStream.push_back(Mungus::ParseAssetHelpers::parseFloat(vertexData.at("posz")));
			vertexDataStream.push_back(Mungus::ParseAssetHelpers::parseFloat(vertexData.at("posw")));
		}


		glBufferData(GL_ARRAY_BUFFER, vertexDataStream.size() * sizeof(float), vertexDataStream.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
	}

	// parse primitives
	{
		auto primitiveBuffers = Mungus::ParseAssetHelpers::parseArray(properties.at("primitives"));

		std::vector<unsigned int> triangleIndices;

		for (auto primitiveBuffer : primitiveBuffers) {
			Mungus::ParseAssetHelpers::Primitive prim = Mungus::ParseAssetHelpers::parsePrimitive(primitiveBuffer);

			switch (prim.primitiveType) {
			case MTRIANGLE:
				for (unsigned int index : prim.indices) {
					triangleIndices.push_back(index);
				}
				break;
			default:
				MLOG("trying to parse unknown primitive type: " << prim.primitiveType)
				break;
			}
		}

		if (!triangleIndices.empty()) {
			renderInfo.triangles = true;
			renderInfo.numTriangles = (unsigned int)triangleIndices.size();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleIndices.size() * sizeof(unsigned int), triangleIndices.data(), GL_STATIC_DRAW);
		}
	}

	// parse shaders
	{
		renderInfo.programId = glCreateProgram();
		int skjdh = 1 + 1;
		glBindAttribLocation(renderInfo.programId, 0, "position");

		auto shaderData = Mungus::ParseAssetHelpers::parseObject(properties.at("shaders"));

		auto vertexShaderBuffers = Mungus::ParseAssetHelpers::parseArray(shaderData.at("vertexShaders"));
		auto fragmentShaderBuffers = Mungus::ParseAssetHelpers::parseArray(shaderData.at("fragmentShaders"));

		for (auto vertexShaderBuffer : vertexShaderBuffers)
			glAttachShader(renderInfo.programId, vertexShaders.at(Mungus::ParseAssetHelpers::parseString(vertexShaderBuffer)));

		for (auto fragmentShaderBuffer : fragmentShaderBuffers)
			glAttachShader(renderInfo.programId, fragmentShaders.at(Mungus::ParseAssetHelpers::parseString(fragmentShaderBuffer)));

		glLinkProgram(renderInfo.programId);

		int programLinked;
		glGetProgramiv(renderInfo.programId, GL_LINK_STATUS, &programLinked);
		if (programLinked != GL_TRUE)
		{
			int log_length = 0;
			char message[1024];
			glGetProgramInfoLog(renderInfo.programId, 1024, &log_length, message);
			MLOG(message)
		}
	}


	glBindVertexArray(0);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}



// parsing helper functions

std::string Mungus::ParseAssetHelpers::getVarName(std::string::iterator& sourceItr) {
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

std::unordered_map<std::string, std::string::iterator> Mungus::ParseAssetHelpers::parseObject(const std::string::iterator& sourceItr) {
	std::string::iterator itr(sourceItr);

	std::stack<char> enclosures;

	std::unordered_map<std::string, std::string::iterator> parameters;
	std::string name;
	std::string::iterator nextParam;

	enclosures.push(*itr);
	itr++;

	while (!enclosures.empty()) {
		if (enclosures.size() == 1 && *itr == '"') {
			name = Mungus::ParseAssetHelpers::getVarName(itr);
			parameters[name] = std::string::iterator(itr);
		}

		if (Mungus::ParseAssetHelpers::enclosureOpenings.find(*itr) != Mungus::ParseAssetHelpers::enclosureOpenings.end())
			enclosures.push(*itr);

		else if (Mungus::ParseAssetHelpers::enclosureEndings.find(*itr) != Mungus::ParseAssetHelpers::enclosureEndings.end() && !enclosures.empty())
			enclosures.pop();

		itr++;
	}

	return parameters;
}

std::vector<std::string::iterator> Mungus::ParseAssetHelpers::parseArray(const std::string::iterator& sourceItr) {
	std::string::iterator itr(sourceItr);

	std::stack<char> enclosures;

	std::vector<std::string::iterator> indexedLocations;

	enclosures.push(*itr);
	itr++;

	if (*itr != ']')
		indexedLocations.push_back(std::string::iterator(itr));

	while (!enclosures.empty()) {
		if (Mungus::ParseAssetHelpers::enclosureOpenings.find(*itr) != Mungus::ParseAssetHelpers::enclosureOpenings.end())
			enclosures.push(*itr);

		else if (Mungus::ParseAssetHelpers::enclosureEndings.find(*itr) != Mungus::ParseAssetHelpers::enclosureEndings.end() && !enclosures.empty())
			enclosures.pop();

		if (enclosures.size() == 1 && *itr == ',')
			indexedLocations.push_back(std::string::iterator(itr + 1));

		itr++;
	}

	return indexedLocations;
}

float Mungus::ParseAssetHelpers::parseFloat(const std::string::iterator& position) {
	std::stringstream stream;
	std::string::iterator itr(position);

	while (Mungus::ParseAssetHelpers::nums.find(*itr) != Mungus::ParseAssetHelpers::nums.end()) {
		stream << *itr;
		itr++;
	}

	return std::stof(stream.str());
}

int Mungus::ParseAssetHelpers::parseInt(const std::string::iterator& position) {
	std::stringstream stream;
	std::string::iterator itr(position);

	while (Mungus::ParseAssetHelpers::nums.find(*itr) != Mungus::ParseAssetHelpers::nums.end()) {
		stream << *itr;
		itr++;
	}

	return std::stoi(stream.str());
}

std::string Mungus::ParseAssetHelpers::parseString(const std::string::iterator& position) {
	std::stringstream stream;
	std::string::iterator itr(position);

	while (*itr != ',' && *itr != ']' && *itr != ')' && *itr != '}') {
		stream << *itr;
		itr++;
	}

	return stream.str();
}

std::vector<float> Mungus::ParseAssetHelpers::parseVertex(const std::string::iterator& vertexBuffer) {
	auto vertexDataBuffer = parseObject(vertexBuffer);
	std::vector<float> vertexData;

	vertexData.push_back(Mungus::ParseAssetHelpers::parseFloat(vertexDataBuffer.at("posx")));
	vertexData.push_back(Mungus::ParseAssetHelpers::parseFloat(vertexDataBuffer.at("posy")));
	vertexData.push_back(Mungus::ParseAssetHelpers::parseFloat(vertexDataBuffer.at("posz")));
	vertexData.push_back(Mungus::ParseAssetHelpers::parseFloat(vertexDataBuffer.at("posw")));

	return vertexData;
}

Mungus::ParseAssetHelpers::Primitive Mungus::ParseAssetHelpers::parsePrimitive(const std::string::iterator& primitiveDataBuffer) {

	std::vector<unsigned int> indices;
	auto primitiveData = Mungus::ParseAssetHelpers::parseObject(primitiveDataBuffer);
	unsigned int primitiveType = Mungus::ParseAssetHelpers::paramCodes.at(Mungus::ParseAssetHelpers::parseString(primitiveData.at("primitiveType")));

	{
		auto vertexIndexBuffers = parseArray(primitiveData.at("vertexIndices"));

		for (auto vertexIndexBuffer : vertexIndexBuffers)
			indices.push_back((unsigned int)(Mungus::ParseAssetHelpers::parseInt(vertexIndexBuffer)));
	}

	return Mungus::ParseAssetHelpers::Primitive{primitiveType, indices};
}
