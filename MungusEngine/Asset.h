#pragma once
#include "stdafx.h"

#define POSX "posx"
#define POSY "posy"
#define POSZ "posz"

namespace Mungus {
	class Shader;
	class VAO;

	class MUNGUS Asset {
	private:
		std::unordered_map<std::string, std::vector<std::vector<float>>> boundingBoxCoords;

	public:
		std::string assetName;
		std::shared_ptr<VAO> vao;
		std::shared_ptr<Shader> program;

		Asset() : program(nullptr) {};
		Asset(	const std::string& name,
				const std::unordered_map<std::string, Shader>& programs);
		virtual ~Asset() {}

		const std::vector<float> getHitboxCoords(const std::string& animation, unsigned int frame) const;

		long findIntersectingVertex(const MungusMath::Line& ray) const;
		void editVertexCoordinate(long vertexId, const MungusMath::MVec3& newPosition);
	};
}
