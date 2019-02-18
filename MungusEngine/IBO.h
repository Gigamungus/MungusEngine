#pragma once

namespace Mungus {

	class IBO {
	private:
		unsigned int id;
		int numTriangleVertices;

	public:
		IBO(const json& indices);
		~IBO();

		const inline unsigned int getId(void) const { return id; }
		int getNumTriangleVertices(void) const { return numTriangleVertices; }
	};

}
