#pragma once
#include "stdafx.h"

namespace Mungus {

	struct VertexAttribute {
		std::string name;
		unsigned int type;
		long offset;

		VertexAttribute(const std::string& name, unsigned int type, long offsetBytes) : 
			name(name),
			type(type),
			offset(offsetBytes)
		{}

		unsigned int getSizeOfElement(void) const;
		long getAttributeOffset(void) const { return offset; }
	};

	class VLO {
	private:
		std::vector<VertexAttribute> attributes;
		std::unordered_map<std::string, int> attributeIndices;

		unsigned int stride;
	public:
		VLO(const std::vector<json>& vertexLayout);

		void push(const std::string& name, unsigned int type) {
			VertexAttribute newElement = Mungus::VertexAttribute( name, type, (long)stride );
			attributes.push_back(newElement);
			stride += (newElement.getSizeOfElement());
		}

		inline const std::vector<VertexAttribute>* getAttributes() const { return &attributes; }
		inline int getIndexOfAttribute(const std::string& attribName) const {
			return attributeIndices.at(attribName);
		}

		inline unsigned int getStride() const { return stride; }
	};

}
