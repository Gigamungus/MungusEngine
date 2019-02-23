#include "stdafx.h"
#include "IBO.h"

Mungus::IBO::IBO(const json& indices) :
	id(0),
	triangles(std::vector<TriangleIndices>()) {
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

	for (std::vector<json> triangle : indices["triangles"]) {
		TriangleIndices tri(triangle[0], triangle[1], triangle[2]);
		triangles.push_back(tri);
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, getNumTriangleVertices() * sizeof(unsigned int), (void*)(triangles.data()), GL_STATIC_DRAW);
}

Mungus::IBO::~IBO() {
	glDeleteBuffers(1, &id);
}
