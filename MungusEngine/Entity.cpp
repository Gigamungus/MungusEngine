#include "stdafx.h"
#include "Entity.h"
#include "Asset.h"

Mungus::Entity::Entity(const Mungus::Asset& source) :
	name(source.assetName),
	entityType(source.assetType),
	programID(source.programID),
	vaoID(source.vaoID)
{}
