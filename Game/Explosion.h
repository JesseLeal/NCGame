#pragma once
#include "Entity.h"
#include "Vector2D.h"

class Explosion : public Entity
{
public:
	Explosion(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Explosion() {}

	void Create(const Vector2D& position);
	void Update();
};