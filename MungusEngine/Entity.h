#pragma once
#include "stdafx.h"

namespace Mungus {

	struct Vertex {
		float x;
		float y;
		float z;
		float w;
	};

	class MUNGUS Entity {
	protected:
		std::string path;
		std::vector<Vertex> vertices;

	public:
		Entity() {}
		Entity(const std::string& assetPath) : path(assetPath) {}
		virtual ~Entity() {}

		const std::string inline getPath() const { return path; }

		void inline addVertex(Vertex vert) { vertices.push_back(vert); }
	};

}
