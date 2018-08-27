#pragma once
#include "Entity.h"
#include "Vector2D.h"

class Missile : public Entity
{
public:
	Missile(Scene* scene) : Entity(scene) {}
	~Missile() {}

	void Create(const Vector2D& position, const Vector2D& direction, float speed, const ID& tag);
	void Update();

	void OnEvent(const Event& event);

protected:
	float m_lifetime;
};