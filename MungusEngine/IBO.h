#pragma once

namespace Mungus {

	class IBO {
	private:
		unsigned int id;
		std::vector<unsigned int> triangleIndices;

	public:
		IBO(const json& indices);
		~IBO();

		const inline unsigned int getId(void) const { return id; }
		int getNumTriangleVertices(void) const { return triangleIndices.size(); }
	};

}
