#include "stdafx.h"
#include "Actor.h"
#include "Asset.h"


Mungus::Actor::Actor(const Mungus::Asset& base) : Entity(base), primitives(base.primitives) {}
