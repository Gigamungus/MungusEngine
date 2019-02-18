#include "stdafx.h"
#include "VBO.h"
#include "VAO.h"
#include "VLO.h"

Mungus::VBO::VBO(const VLO & layout, const std::vector<json> & vertices) : id(0) {

	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);

	unsigned int dataSize = layout.getStride() * vertices.size();
	char* data = new char[dataSize];
	auto attributes = *layout.GetAttributes();
	int i = 0;
	int j = 0;

	for (json vertex : vertices) {
		for (Mungus::VertexAttribute attribute : attributes) {
			switch (attribute.type) {
			case GL_BYTE: {
				char value = (int)vertex[attribute.name];
				*(char*)(&data[i]) = value;
				i += sizeof(char);
				break;
			}
			case GL_UNSIGNED_BYTE: {
				unsigned char value = (unsigned int)vertex[attribute.name];
				*(unsigned char*)(&data[i]) = value;
				i += sizeof(unsigned char);
				break;
			}
			case GL_SHORT: {
				short value = vertex[attribute.name];
				*(short*)(&data[i]) = value;
				i += sizeof(short);
				break;
			}
			case GL_UNSIGNED_SHORT: {
				short value = vertex[attribute.name];
				*(short*)(&data[i]) = value;
				i += sizeof(unsigned short);
				break;
			}
			case GL_INT: {
				int value = vertex[attribute.name];
				*(int*)(&data[i]) = value;
				i += sizeof(int);
				break;
			}
			case GL_UNSIGNED_INT: {
				int value = vertex[attribute.name];
				*(int*)(&data[i]) = value;
				i += sizeof(unsigned int);
				break;
			}
			case GL_FLOAT: {
				float value = vertex[attribute.name];
				*(float*)(&data[i]) = value;
				i += sizeof(float);
				break;
			}
			case GL_DOUBLE: {
				double value = vertex[attribute.name];
				*(double*)(&data[i]) = value;
				i += sizeof(double);
				break;
			}
			default:
				MLOG("trying to load data of unknown type from mungass: " << attribute.type)
				break;
			}
		}
	}

	i = 0;

	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

	for (Mungus::VertexAttribute attribute : *layout.GetAttributes()) {
		glVertexAttribPointer(i, 1, attribute.type, GL_FALSE, layout.getStride(), (const void*)j);
		glEnableVertexAttribArray(i);
		i++;
		j += sizeMap.at(attribute.type);
	}

	delete[] data;
}

Mungus::VBO::~VBO() {
	glDeleteBuffers(1, &id);
}
