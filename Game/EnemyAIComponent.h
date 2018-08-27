#pragma once
#include "ControllerComponent.h"

class EnemyAIComponent : public IControllerComponent
{
public:
	EnemyAIComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed = 1.0f);
	void Destroy();
	void Update();

protected:
	float m_speed;
	float m_cooldown;
	float m_firerateMin = 0.7f;
	float m_firerateMax = 2.4f;
};