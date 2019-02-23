#pragma once
#include "stdafx.h"

namespace Mungus {

	class VLO;
	struct TriangleIndices;

	class VBO {
	private:
		unsigned int id;
		std::shared_ptr<VLO> vertexLayout;
		std::shared_ptr<std::vector<json>> vertices;
		std::unordered_map<unsigned int, std::unordered_set<unsigned int>> connections;

	public:
		VBO(std::shared_ptr<VLO> layout, const std::vector<json>& vertices);
		virtual ~VBO();

		void bind(void) const { glBindBuffer(GL_ARRAY_BUFFER, id); }
		void unbind(void) const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

		std::shared_ptr<VLO> getLayout(void) const { return vertexLayout; }
		std::shared_ptr<std::vector<json>> getVertices(void) const { return vertices; }
		void moveVertex(int id, MungusMath::MVec3 newPosition);
		void addConnections(const Mungus::TriangleIndices& connectedVertices);
		inline const std::unordered_set<unsigned int>* getVertexConnections(unsigned int vertex) const {
			return &connections.at(vertex);
		}
		MungusMath::MVec3 getVertexPosition(unsigned int vertexId) const;
		float getDistanceBetweenVertices(unsigned int vert1, unsigned int vert2) const;
		inline const std::unordered_set<unsigned int>* getConnectedVertices(unsigned int vertexId) const {
			return &connections.at(vertexId);
		}
	};

}
