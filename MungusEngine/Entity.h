#pragma once
#include "stdafx.h"

namespace Mungus {

	struct MVec4 {
		float x;
		float y;
		float z;
		float w;
	};

	struct MVec3 {
		float x;
		float y;
		float z;
	};

	struct Primitive {
		unsigned int primType;
		std::vector<unsigned int> vertexIndices;
		MVec4 surfaceColor;
	};

	struct Triangle : public Primitive {
		MVec3 surfaceNormal;
	};

	class MUNGUS Entity {
	private:
		const unsigned int entityType;
		std::string path;

	protected:

	public:
		Entity(const std::string& assetPath, const unsigned int entityType) :
			path(assetPath),
			entityType(entityType)
		{}

		virtual ~Entity() {}

		const std::string inline getPath() const { return path; }
		const unsigned int inline type() const { return entityType; }
	};

}
