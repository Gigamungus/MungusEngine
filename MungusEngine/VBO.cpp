#include "stdafx.h"
#include "VBO.h"
#include "VAO.h"
#include "VLO.h"

Mungus::VBO::VBO(std::shared_ptr<VLO> layout, const std::vector<json>& vertexJSON) :
	id(0),
	vertexLayout(layout),
	vertices(std::make_shared<std::vector<json>>(vertexJSON)) {
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);

	unsigned int dataSize = layout->getStride() * vertexJSON.size();
	char* data = new char[dataSize];
	auto attributes = *layout->getAttributes();
	int i = 0;
	int j = 0;

	for (json vertex : vertexJSON) {
		int attributeIndex = 0;

		for (Mungus::VertexAttribute attribute : attributes) {
			switch (attribute.type) {
			case GL_BYTE: {
				char value = (int)vertex[attributeIndex];
				*(char*)(&data[i]) = value;
				i += sizeof(char);
				break;
			}
			case GL_UNSIGNED_BYTE: {
				unsigned char value = (unsigned int)vertex[attributeIndex];
				*(unsigned char*)(&data[i]) = value;
				i += sizeof(unsigned char);
				break;
			}
			case GL_SHORT: {
				short value = vertex[attributeIndex];
				*(short*)(&data[i]) = value;
				i += sizeof(short);
				break;
			}
			case GL_UNSIGNED_SHORT: {
				short value = vertex[attributeIndex];
				*(short*)(&data[i]) = value;
				i += sizeof(unsigned short);
				break;
			}
			case GL_INT: {
				int value = vertex[attributeIndex];
				*(int*)(&data[i]) = value;
				i += sizeof(int);
				break;
			}
			case GL_UNSIGNED_INT: {
				int value = vertex[attributeIndex];
				*(int*)(&data[i]) = value;
				i += sizeof(unsigned int);
				break;
			}
			case GL_FLOAT: {
				float value = vertex[attributeIndex];
				*(float*)(&data[i]) = value;
				i += sizeof(float);
				break;
			}
			case GL_DOUBLE: {
				double value = vertex[attributeIndex];
				*(double*)(&data[i]) = value;
				i += sizeof(double);
				break;
			}
			default:
				MLOG("trying to load data of unknown type from mungass: " << attribute.type)
				break;
			}
			attributeIndex++;
		}
	}

	i = 0;

	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

	for (Mungus::VertexAttribute attribute : *layout->getAttributes()) {
		glVertexAttribPointer(i, 1, attribute.type, GL_FALSE, layout->getStride(), (const void*)j);
		glEnableVertexAttribArray(i);
		i++;
		j += sizeMap.at(attribute.type);
	}

	delete[] data;
}

Mungus::VBO::~VBO() {
	glDeleteBuffers(1, &id);
}

void Mungus::VBO::moveVertex(int id, MungusMath::MVec3 newPosition) {
	std::vector<json> vertex = (*vertices)[id];
	auto attribs = *vertexLayout->getAttributes();
	auto xPosIndex = vertexLayout->getIndexOfAttribute("posx");
	auto yPosIndex = vertexLayout->getIndexOfAttribute("posy");
	auto zPosIndex = vertexLayout->getIndexOfAttribute("posz");

	vertex[xPosIndex] = newPosition.x;
	vertex[yPosIndex] = newPosition.y;
	vertex[zPosIndex] = newPosition.z;

	long xOffset = attribs[xPosIndex].getAttributeOffset();
	long yOffset = attribs[yPosIndex].getAttributeOffset();
	long zOffset = attribs[zPosIndex].getAttributeOffset();

	bind();

	void* data = glMapBufferRange(
		GL_ARRAY_BUFFER,
		vertexLayout->getStride() * id,
		vertexLayout->getStride(), 
		GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT);

	char* mappableData = (char*)data;
	char* xByteData = &mappableData[xOffset];
	char* yByteData = &mappableData[yOffset];
	char* zByteData = &mappableData[zOffset];
	float* xData = (float*)(xByteData);
	float* yData = (float*)(yByteData);
	float* zData = (float*)(zByteData);

	*xData += newPosition.x;
	*yData += newPosition.y;
	*zData += newPosition.z;

	glUnmapBuffer(GL_ARRAY_BUFFER);

	unbind();
}
