#include "stdafx.h"
#include "VLO.h"
#include "VAO.h"

unsigned int Mungus::VertexAttribute::getSizeOfElement(void) const {
	return sizeMap.at(type);
}


Mungus::VLO::VLO(const std::vector<json>& vertexLayout) :
	stride(0),
	attributes(std::vector<VertexAttribute>()),
	attributeIndices(std::unordered_map<std::string, int>()){
	int i = 0;
	for (json attrib : vertexLayout) {
		for (auto& [key, value] : attrib.items()) {
			push(key, typeMap.at(value));
			attributeIndices[key] = i;
		}
		i++;
	}
}
