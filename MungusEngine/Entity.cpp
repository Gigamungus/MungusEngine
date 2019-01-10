#include "stdafx.h"
#include "Entity.h"
#include "Asset.h"

Mungus::Entity::Entity() :
	orientation(MungusMath::MMat4::identity()),
	position({ 0, 0, 0 })
{}



