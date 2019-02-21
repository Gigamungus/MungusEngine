#pragma once
#include "stdafx.h"

namespace Mungus {
	class Shader;

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

	class VBO;
	class IBO;

	class VAO {
	private:
		unsigned int id;
		std::shared_ptr<VBO> vbo;
		std::shared_ptr<IBO> ibo;
		int numTriangleVertices;

	public:
		VAO(void) {}
		VAO(const Shader& program, const std::vector<json>& vertices, const json& primitives);
		virtual ~VAO();

		unsigned int getId(void) const { return id; }
		int getNumTriangleVertices(void) const { return numTriangleVertices; };
	};

}