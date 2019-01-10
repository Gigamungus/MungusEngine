#include "stdafx.h"
#include "Actor.h"
#include "Asset.h"


Mungus::Actor::Actor(const Mungus::Asset& source, unsigned long id) :
	name(source.assetName),
	id(id),
	renderInfo(&source.renderInfo),
	scale(MungusMath::MMat4::scale(1.0f, 1.0f, 1.0f))
{}


const Mungus::RenderInfo inline Mungus::Actor::getRenderInfo(void) const { return *renderInfo; }
