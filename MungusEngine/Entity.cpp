#include "stdafx.h"
#include "Entity.h"
#include "Asset.h"

Mungus::Entity::Entity(const Mungus::Asset& source, unsigned long id) :
	name(source.assetName),
	id(id),
	renderInfo(&source.renderInfo)
{}

const Mungus::RenderInfo inline Mungus::Entity::getRenderInfo(void) const { return *renderInfo; }
