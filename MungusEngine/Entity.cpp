#include "stdafx.h"
#include "Entity.h"
#include "Asset.h"

Mungus::Entity::Entity(const Mungus::Asset& source) :
	name(source.assetName),
	renderInfo(&source.renderInfo)
{}

const Mungus::RenderInfo inline Mungus::Entity::getRenderInfo(void) const { return *renderInfo; }
