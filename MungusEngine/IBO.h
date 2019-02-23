#pragma once
#include "stdafx.h"

namespace Mungus {

	struct TriangleIndices {
		unsigned int index1;
		unsigned int index2;
		unsigned int index3;

		TriangleIndices(unsigned int first, unsigned int second, unsigned int third) :
			index1(first),
			index2(second),
			index3(third)
		{}
	};

	class IBO {

	private:
		unsigned int id;
		std::vector<TriangleIndices> triangles;

	public:
		IBO(const json& indices);
		~IBO();

		const inline unsigned int getId(void) const { return id; }
		inline int getNumTriangleVertices(void) const { return triangles.size() * 3; }
		inline const std::vector<TriangleIndices>* getTriangleIndices(void) const { return &triangles; }
	};

}
