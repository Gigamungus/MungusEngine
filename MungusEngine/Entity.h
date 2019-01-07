#pragma once
#include "stdafx.h"
#include "../Resources/MungusLibs/MungusMath.h"

namespace Mungus {

	struct Primitive {
		unsigned int primType;
		std::vector<unsigned int> vertexIndices;
		MungusMath::MVec4 surfaceColor;
	};

	struct Triangle : public Primitive {
		MungusMath::MVec3 surfaceNormal;
	};

	class MUNGUS Entity {
	private:
		const unsigned int entityType;
		std::string path;

	public:
		Entity(const std::string& assetPath, const unsigned int entityType) :
			path(assetPath),
			entityType(entityType)
		{}

		virtual ~Entity() {}

		const std::string inline getPath() const { return path; }
		const unsigned int inline type() const { return entityType; }
	};

	struct ParseAssetFunctions {
		static const std::unordered_map<std::string, int> paramCodes;
		static const std::unordered_set<char> enclosureOpenings;
		static const std::unordered_set<char> enclosureEndings;
		static const std::unordered_set<char> nums;

		// get the name of a variable, iterator should start at the first quote, and will end after the colon
		static std::string getVarName(std::string::iterator& sourceItr);

		// break a general buffered collection of data into a tangible collection of iterators at each element
		static std::unordered_map<std::string, std::string::iterator> parseObject(const std::string::iterator& itr);
		static std::vector<std::string::iterator> parseArray(const std::string::iterator& itr);

		// get integral values from buffer locations
		static float parseFloat(const std::string::iterator& position);
		static int parseInt(const std::string::iterator& position);
		static std::string parseString(const std::string::iterator& position);

		// parse more specific collection types into a relevant tangible container
		static MungusMath::MVec4 parseVertex(const std::string::iterator& itr);
		static Mungus::Primitive parsePrimitive(const std::string::iterator& primitiveDataBuffer);
	};

}
