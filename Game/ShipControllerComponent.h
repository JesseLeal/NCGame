#pragma once
#include "ControllerComponent.h"

class ShipControllerComponent : public IControllerComponent
{
public:
	ShipControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed = 1.0f);
	void Destroy();
	void Update();

protected:
	float m_speed;
	float m_cooldown = 0.0f;
};