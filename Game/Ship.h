#pragma once
#include "Entity.h"
#include "Vector2D.h"

class Ship : public Entity
{
public:
	Ship(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Ship() {}

	void Create(const Vector2D& position);
	void Update();

	void OnEvent(const Event& event);
};