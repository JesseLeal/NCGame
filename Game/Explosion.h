#pragma once
#include "Entity.h"
#include "Vector2D.h"

class Explosion : public Entity
{
public:
	enum eType
	{
		ENEMY,
		PLAYER
	};

public:
	Explosion(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Explosion() {}

	void Create(const Vector2D& position, eType type);
	void Update();

	eType GetType()
	{
		return m_type;
	}

protected:
	eType m_type;
};