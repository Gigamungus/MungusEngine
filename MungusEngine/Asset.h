#pragma once
#include "stdafx.h"

namespace Mungus {

	struct RenderInfo {
		unsigned int assetType;
		unsigned int programId = 0;
		unsigned int VAO = 0;
		bool triangles = false;
		unsigned int numTriangleVertices = 0;
		void* trianglesOffset = 0;
	};

	class MUNGUS Asset {
	public:
		std::string assetName;
		struct RenderInfo renderInfo;
		MungusMath::MVec3 backHitboxCoord;
		MungusMath::MVec3 frontHitboxCoord;

		Asset() {};
		Asset(	const std::string& name,
				const std::unordered_map<std::string, const unsigned int>& vertexShaders,
				const std::unordered_map<std::string, const unsigned int>& fragmentShaders);
		virtual ~Asset() {}
	};


	struct ParseAssetHelpers {
		struct Primitive {
			unsigned int primitiveType;
			std::vector<unsigned int> indices;
		};

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
		static std::vector<float> parseVertex(const std::string::iterator& itr);
		static Primitive parsePrimitive(const std::string::iterator& primitiveDataBuffer);
	};

}
