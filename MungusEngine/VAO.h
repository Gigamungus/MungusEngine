#pragma once
#include "stdafx.h"

namespace Mungus {
	class Shader;
	struct BoundingBox;

	static std::unordered_map<std::string, unsigned int> typeMap = {
		{"byte", GL_BYTE},
		{"unsigned byte", GL_UNSIGNED_BYTE},
		{"short", GL_SHORT},
		{"unsigned short", GL_UNSIGNED_SHORT},
		{"int", GL_INT},
		{"unsigned int", GL_UNSIGNED_INT},
		{"float", GL_FLOAT},
		{"double", GL_DOUBLE}
	};

	static std::unordered_map<unsigned int, unsigned int> sizeMap = {
		{GL_BYTE, sizeof(char)},
		{GL_UNSIGNED_BYTE, sizeof(unsigned char)},
		{GL_UNSIGNED_SHORT, sizeof(unsigned short)},
		{GL_UNSIGNED_SHORT, sizeof(unsigned short)},
		{GL_INT, sizeof(int)},
		{GL_UNSIGNED_INT, sizeof(unsigned int)},
		{GL_FLOAT, sizeof(float)},
		{GL_DOUBLE, sizeof(double)}
	};

	class VAO;
	class VBO;
	class IBO;
	template <typename T> class AABBTree;

	struct VertexPosition {
		MungusMath::MVec3 position;
		std::shared_ptr<VAO> owner;
		int id;

		VertexPosition(float x, float y, float z, int id, std::shared_ptr<VAO> owner) :
			position(MungusMath::MVec3(x, y, z)),
			id(id),
			owner(owner)
		{}

		MungusMath::MVec3 getPosition(void) const {
			return position;
		}
		std::shared_ptr<Mungus::BoundingBox> getBoundingBox(void) const;
		void setPosition(const MungusMath::MVec3& newPosition);
	};

	class VAO {
	private:
		unsigned int id;
		std::shared_ptr<VBO> vbo;
		std::shared_ptr<IBO> ibo;
		std::shared_ptr<AABBTree<VertexPosition>> vertexTree;

	public:
		VAO(void) {}
		VAO(const Shader& program, const std::vector<json>& vertices, const json& primitives);
		virtual ~VAO();

		inline unsigned int getId(void) const { return id; }
		int getNumTriangleVertices(void) const;
		void moveVertex(long id, MungusMath::MVec3 newPosition);
		void updateVertexRenderPosition(int id, MungusMath::MVec3 newPosition);
		long findIntersectingVertex(const MungusMath::Line& ray) const;
		const std::unordered_set<unsigned int>* getConnectedVertices(unsigned int vertexId) const;
		float getDistanceBetweenVertices(unsigned int vert1, unsigned int vert2) const;
	};

}
