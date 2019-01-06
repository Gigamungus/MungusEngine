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
