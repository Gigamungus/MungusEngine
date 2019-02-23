#include "stdafx.h"
#include "VAO.h"
#include "VLO.h"
#include "VBO.h"
#include "IBO.h"
#include "Shader.h"
#include "AABBTree.h"

Mungus::VAO::VAO(const Shader& program, const std::vector<json>& vertices, const json& primitives) :
	id(0),
	ibo(nullptr),
	vbo(nullptr),
	vertexTree(std::make_shared<Mungus::AABBTree<Mungus::VertexPosition>>())
{

	glGenVertexArrays(1, &id);
	glBindVertexArray(id);

	vbo = std::make_shared<VBO>(program.getLayout(), vertices);
	ibo = std::make_shared<IBO>(primitives);

	int i = 0;

	for (json vertex : *vbo->getVertices()) {
		vertexTree->insert(std::make_shared<Mungus::VertexPosition>(
			vertex[vbo->getLayout()->getIndexOfAttribute("posx")],
			vertex[vbo->getLayout()->getIndexOfAttribute("posy")],
			vertex[vbo->getLayout()->getIndexOfAttribute("posz")],
			i, std::make_shared<Mungus::VAO>(*this)), i);
		i++;
	}

	glBindVertexArray(0);
}

Mungus::VAO::~VAO() {
	ibo = nullptr;
	vbo = nullptr;
}

int Mungus::VAO::getNumTriangleVertices(void) const {
	return ibo->getNumTriangleVertices();
}

void Mungus::VAO::moveVertex(long id, MungusMath::MVec3 newPosition) {
	vertexTree->setElementPosition(id, newPosition);
}

void Mungus::VAO::updateVertexRenderPosition(int id, MungusMath::MVec3 newPosition) {
	vbo->moveVertex(id, newPosition);
}

long Mungus::VAO::findIntersectingVertex(const MungusMath::Line & ray) const {
	return vertexTree->findFirstIntersecting(ray);
}

std::shared_ptr<Mungus::BoundingBox> Mungus::VertexPosition::getBoundingBox(void) const {
	float vertexRadius = 0.1;
	MungusMath::MVec3 offset(vertexRadius, vertexRadius, vertexRadius);
	MungusMath::MVec3 lowerBound = position - offset;
	MungusMath::MVec3 upperBound = position + offset;
	float tmp = lowerBound.z;
	lowerBound.z = -upperBound.z;
	upperBound.z = -tmp;
	return std::make_shared<Mungus::BoundingBox>((unsigned long)id, lowerBound, upperBound);
}

void Mungus::VertexPosition::setPosition(const MungusMath::MVec3 & newPosition) {
	position = newPosition;
	owner->updateVertexRenderPosition(id, newPosition);
}
