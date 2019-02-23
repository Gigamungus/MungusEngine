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

	ibo = std::make_shared<IBO>(primitives);
	vbo = std::make_shared<VBO>(program.getLayout(), vertices);
	const std::vector<TriangleIndices> triangleIndices = *ibo->getTriangleIndices();

	for (TriangleIndices indices : triangleIndices) {
		vbo->addConnections(indices);
	}

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

const std::unordered_set<unsigned int>* Mungus::VAO::getConnectedVertices(unsigned int vertexId) const {
	return vbo->getConnectedVertices(vertexId);;
}

float Mungus::VAO::getDistanceBetweenVertices(unsigned int vert1, unsigned int vert2) const {
	return vbo->getDistanceBetweenVertices(vert1, vert2);
}

std::shared_ptr<Mungus::BoundingBox> Mungus::VertexPosition::getBoundingBox(void) const {
	float vertexRadius = std::numeric_limits<float>::infinity();
	for (unsigned int connectedVertex : *owner->getConnectedVertices(id)) {
		float connectionLength = owner->getDistanceBetweenVertices(id, connectedVertex);
		if (connectionLength < vertexRadius) {
			vertexRadius = connectionLength;
		}
	}

	vertexRadius = (vertexRadius == std::numeric_limits<float>::infinity()) ? 0.1 : vertexRadius / 4.0;

	std::cout << "vertex: " << id << " given hitbox radius of: " << vertexRadius << "\n";

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
