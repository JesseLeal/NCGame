#pragma once
#include "ControllerComponent.h"
#include "Vector2D.h"

class ENGINE_API TransformControllerComponent : public IControllerComponent
{
public:
	TransformControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(const Vector2D& position, float rotation, float rotateRate, float speed = 1.0f);
	void Destroy();
	void Update();

protected:
	Vector2D m_position;
	float m_speed = 0.0f;
	float m_rotation;
	float m_rotateRate = 0.0f;
};