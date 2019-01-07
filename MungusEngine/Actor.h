#pragma once
#include "stdafx.h"
#include "Entity.h"

namespace Mungus {

	class MUNGUS Actor : public Entity {
	private:
		std::vector<MungusMath::MVec4> vertices;
		std::vector<Primitive> primitives;
		std::vector<std::string> vertexShaders;
		std::vector<std::string> fragmentShaders;

	public:
		Actor(const std::string& assetPath, const unsigned int entityType, std::string::iterator& itr);
		virtual ~Actor() {};

		void inline addVertex(const MungusMath::MVec4& vert) { vertices.push_back(vert); }
		void inline addPrimitive(const Primitive& prim) { primitives.push_back(prim); }
		void inline addVertexShader(const std::string& shader) { vertexShaders.push_back(shader); }
		void inline addFragmentShader(const std::string& shader) { fragmentShaders.push_back(shader); }
	};

}