#include "stdafx.h"
#include "IBO.h"

Mungus::IBO::IBO(const json& indices) : id(0), numTriangleVertices(0) {
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

	std::vector<unsigned int> triangleIndices;

	for (std::vector<json> triangle : indices["triangles"]) {
		for (unsigned int value : triangle) {
			triangleIndices.push_back(value);
		}
	}

	numTriangleVertices = triangleIndices.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleIndices.size() * sizeof(unsigned int), triangleIndices.data(), GL_STATIC_DRAW);
}

Mungus::IBO::~IBO() {
	glDeleteBuffers(1, &id);
}
