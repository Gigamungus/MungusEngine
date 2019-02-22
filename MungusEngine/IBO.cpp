#include "stdafx.h"
#include "IBO.h"

Mungus::IBO::IBO(const json& indices) :
	id(0),
	triangleIndices(std::vector<unsigned int>()) {
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

	for (std::vector<json> triangle : indices["triangles"]) {
		for (unsigned int value : triangle) {
			triangleIndices.push_back(value);
		}
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleIndices.size() * sizeof(unsigned int), triangleIndices.data(), GL_STATIC_DRAW);
}

Mungus::IBO::~IBO() {
	glDeleteBuffers(1, &id);
}
