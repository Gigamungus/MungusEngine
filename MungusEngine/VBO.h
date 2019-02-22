#pragma once
#include "stdafx.h"

namespace Mungus {

	class VLO;

	class VBO {
	private:
		unsigned int id;
		std::shared_ptr<VLO> vertexLayout;
		std::shared_ptr<std::vector<json>> vertices;

	public:
		VBO(std::shared_ptr<VLO> layout, const std::vector<json>& vertices);
		virtual ~VBO();

		void bind(void) const { glBindBuffer(GL_ARRAY_BUFFER, id); }
		void unbind(void) const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

		std::shared_ptr<VLO> getLayout(void) const { return vertexLayout; }
		std::shared_ptr<std::vector<json>> getVertices(void) const { return vertices; }
		void moveVertex(int id, MungusMath::MVec3 newPosition);
	};

}
