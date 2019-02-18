#pragma once
#include "stdafx.h"

namespace Mungus {

	struct VertexAttribute {
		std::string name;
		unsigned int type;

		unsigned int getSizeOfElement(void) const;
	};

	class VLO {
	private:
		std::vector<VertexAttribute> attributes;
		unsigned int stride;
	public:
		VLO(const std::vector<json>& vertexLayout);

		void push(const std::string& name, unsigned int type) {
			VertexAttribute newElement = { name, type };
			attributes.push_back(newElement);
			stride += (newElement.getSizeOfElement());
		}

		inline const std::vector<VertexAttribute>* GetAttributes() const { return &attributes; }

		inline unsigned int getStride() const { return stride; }
	};

}
