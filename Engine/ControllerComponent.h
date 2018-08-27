#pragma once

#include "Component.h"

class ENGINE_API IControllerComponent : public Component
{
public:
	IControllerComponent(Entity* owner) : Component(owner) {}
};