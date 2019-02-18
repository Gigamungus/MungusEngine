#include "stdafx.h"
#include "VAO.h"
#include "VLO.h"
#include "VBO.h"
#include "IBO.h"
#include "Shader.h"

Mungus::VAO::VAO(const Shader& program, const std::vector<json>& vertices, const json& primitives) :
	id(0),
	numTriangleVertices(0),
	ibo(nullptr),
	vbo(nullptr) {

	glGenVertexArrays(1, &id);
	glBindVertexArray(id);

	vbo = std::make_shared<VBO>(program.getLayout(), vertices);
	ibo = std::make_shared<IBO>(primitives);

	numTriangleVertices = ibo->getNumTriangleVertices();

	glBindVertexArray(0);
	ibo = nullptr;
	vbo = nullptr;
}

Mungus::VAO::~VAO() {

}
