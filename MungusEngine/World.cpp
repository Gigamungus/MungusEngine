#include "stdafx.h"
#include "World.h"
#include "Actor.h"

#include "../Resources/MungusLibs/MungusMath.h"
#include "../Resources/MungusLibs/MungusUtil.h"

#define MVERTICES 1
#define MPOSX 2
#define MPOSY 3
#define MPOSZ 4
#define MPOSW 5
#define MPRIMITIVES 6
#define MPRIMITIVETYPE 7
#define MVERTEXINDICIES 8
#define MSURFACENORMAL 9
#define MSURFACECOLOR 10
#define MSHADERSTOUSE 11
#define MVERTEXSHADERS 12
#define MFRAGMENTSHADERS 13


static std::unordered_map<std::string, int> paramCodes = {
	{
		{"vertices", MVERTICES},
		{"posx", MPOSX},
		{"posy", MPOSY},
		{"posz", MPOSZ},
		{"posw", MPOSW},
		{"primitives", MPRIMITIVES},
		{"primitiveType", MPRIMITIVETYPE},
		{"vertexIndices", MVERTEXINDICIES},
		{"surfaceNormal", MSURFACENORMAL},
		{"surfaceColor", MSURFACECOLOR},
		{"shadersToUse", MSHADERSTOUSE},
		{"vertexShaders", MVERTEXSHADERS},
		{"fragmentShaders", MFRAGMENTSHADERS}
	}
};

struct CompileState {
	std::vector<Mungus::Vertex> vertices;


};

void parseVertices(std::string::iterator* sourceItr, std::string::iterator* sourceEnd, std::shared_ptr<Mungus::Entity>& entity);
void parseVertex(std::string::iterator* sourceItr, std::string::iterator* sourceEnd, std::shared_ptr<Mungus::Entity>& entity);

void parsePrimitives(std::string::iterator* sourceItr, std::string::iterator* sourceEnd, std::shared_ptr<Mungus::Entity>& entity);
void parsePrimitive(std::string::iterator* sourceItr, std::string::iterator* sourceEnd, std::shared_ptr<Mungus::Entity>& entity);


void Mungus::World::loadAsset(const std::string& assetPath) {
	std::string assetSource = MungusUtil::getTextFromFile(std::filesystem::current_path().string() + "/../resources/assets/" + assetPath + ".txt");
	entities.push_back(createEntityFromSourceString(assetPath, assetSource));
}

std::shared_ptr<Mungus::Entity> Mungus::World::createEntityFromSourceString(const std::string & sourcePath, const std::string & source) {
	std::string sourceText = MungusUtil::removeAllWhiteSpace(&source);
	std::shared_ptr<Mungus::Entity> ptr;
	std::stringstream entityType;

	auto sourceItr = sourceText.begin();
	auto sourceEnd = sourceText.end();
	
	while (*sourceItr != '{') {
		entityType << *sourceItr;
		sourceItr++;
	}

	std::string type = entityType.str();

	if (type == "actor") {
		ptr = std::make_shared<Mungus::Actor>(sourcePath);
	}
	else {
		MLOG("trying to load unsupported asset type: " << type);
		return ptr;
	}

	sourceItr++;

	CompileState state;

	////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////                       ///////////////////////////////
	//////////////////////////////       PARSER          ///////////////////////////////
	//////////////////////////////                       ///////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////



	while (*sourceItr != '}') {
		// skip first quote of parameter name
		sourceItr++;

		std::stringstream paramNameStream;

		// put parameter name into paramNameStream
		while (*sourceItr != '"') {
			paramNameStream << *sourceItr;
			sourceItr++;
		}

		// skip end quote and colon
		sourceItr += 2;

		std::string paramName = paramNameStream.str();

		// parse the parameter's data based on name
		if (paramCodes.find(paramName) == paramCodes.end())
			MLOG("unrecognized parameter name in asset: " << sourcePath)

		else {
			switch (paramCodes.at(paramName)) {
			case MVERTICES:
				parseVertices(&sourceItr, &sourceEnd, ptr);
				break;

			case MPRIMITIVES:
				parsePrimitives(&sourceItr, &sourceEnd, ptr);
				break;

			default:
				MLOG("unrecognized parameter name in asset: " << sourcePath)
			}
		}
		
	}

	////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////                       ///////////////////////////////
	//////////////////////////////       PARSER          ///////////////////////////////
	//////////////////////////////                       ///////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////

	return ptr;
}

// process an array of vertices
void parseVertices(std::string::iterator* sourceItr, std::string::iterator* sourceEnd, std::shared_ptr<Mungus::Entity>& entity) {
	MASSERT(**sourceItr == '[', "problem parsing vertices attribute on asset: " << entity->getPath())

	// skip initial bracket
	(*sourceItr)++;

	// while there are more vertices
	while (**sourceItr == '{') {
		parseVertex(sourceItr, sourceEnd, entity);
		if (**sourceItr == ',')
			(*sourceItr)++;
	}
	// no more vertices, go to next item
	(*sourceItr)++;
	if ((**sourceItr) == ',')
		(*sourceItr)++;
}

// process a single vertex
void parseVertex(std::string::iterator* sourceItr, std::string::iterator* sourceEnd, std::shared_ptr<Mungus::Entity>& entity) {
	MASSERT(**sourceItr == '{', "problem parsing vertex attribute on asset: " << entity->getPath())

	// vertex to build
	Mungus::Vertex vert;

	// reusable vars
	std::stringstream vertexParamNameStream;
	std::string vertexParamName;
	std::stringstream paramValueStream;
	float paramValue;

	// while there are more attributes
	while ((**sourceItr) != '}') {

		// skip the opening brace/trailing commas
		(*sourceItr)+= 2;

		// while there are more characters in the name
		while ((**sourceItr) != '"') {
			vertexParamNameStream << (**sourceItr);
			(*sourceItr)++;
		}

		vertexParamName = vertexParamNameStream.str();

		// skip ending quote and colon
		(*sourceItr) += 2;


		if (paramCodes.find(vertexParamName) == paramCodes.end())
			MLOG("unrecognized parameter name in asset: " << entity->getPath())

		else {
			switch (paramCodes.at(vertexParamName)) {
			case MPOSX: {
				// posx attribute, get the value as a string, convert to float, and add to vertex
				while ((**sourceItr) != ',' && (**sourceItr) != '}') {
					paramValueStream << (**sourceItr);
					(*sourceItr)++;
				}
				vert.x = std::stof(paramValueStream.str());
				break;
			}
			case MPOSY: {
				// posy attribute, get the value as a string, convert to float, and add to vertex
				while ((**sourceItr) != ',' && (**sourceItr) != '}') {
					paramValueStream << (**sourceItr);
					(*sourceItr)++;
				}
				vert.y = std::stof(paramValueStream.str());
				break;
			}
			case MPOSZ: {
				// posz attribute, get the value as a string, convert to float, and add to vertex
				while ((**sourceItr) != ',' && (**sourceItr) != '}') {
					paramValueStream << (**sourceItr);
					(*sourceItr)++;
				}
				vert.z = std::stof(paramValueStream.str());
				break;
			}
			case MPOSW: {
				// posw attribute, get the value as a string, convert to float, and add to vertex
				while ((**sourceItr) != ',' && (**sourceItr) != '}') {
					paramValueStream << (**sourceItr);
					(*sourceItr)++;
				}
				vert.w = std::stof(paramValueStream.str());
				break;
			}
			default:
				MLOG("unrecognized parameter name in asset: " << entity->getPath())
			}
		}
		vertexParamNameStream.str("");
		vertexParamNameStream.clear();
		paramValueStream.str("");
		paramValueStream.clear();
	}
	(*sourceItr)++;
	if ((**sourceItr) == ',')
		(*sourceItr)++;

	entity->addVertex(vert);
}

// process an array of primitves
void parsePrimitives(std::string::iterator* sourceItr, std::string::iterator* sourceEnd, std::shared_ptr<Mungus::Entity>& entity) {
	MASSERT(**sourceItr == '[', "problem parsing primitives attribute on asset: " << entity->getPath())

	// skip initial bracket
	(*sourceItr)++;

	// while there are more primitives
	while (**sourceItr == '{') {
		parsePrimitive(sourceItr, sourceEnd, entity);
		if (**sourceItr == ',')
			(*sourceItr)++;
	}

	// no more primitives, go to next item
	(*sourceItr)++;
	if ((**sourceItr) == ',')
		(*sourceItr)++;
}

// process a single primitive
void parsePrimitive(std::string::iterator* sourceItr, std::string::iterator* sourceEnd, std::shared_ptr<Mungus::Entity>& entity) {

}