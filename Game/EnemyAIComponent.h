#pragma once
#include "ControllerComponent.h"

class EnemyAIComponent : public IControllerComponent
{
public:
	EnemyAIComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create();
	void Destroy();
	void Update();

protected:
	float m_cooldown;
	float m_firerateMin = 5.0f;
	float m_firerateMax = 10.0f;
};