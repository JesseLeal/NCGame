#pragma once
#include "Component.h"
#include "Vector2D.h"

class ENGINE_API IPhysicsComponent : public Component
{
public:
	enum eForceType
	{
		FORCE,//keep applying
		IMPULSE,//one big push, like boom
		VELOCITY//const speed
	};

public:
	IPhysicsComponent(Entity* owner) : Component(owner) {}

	virtual void SetVelocity(const Vector2D& velocity) = 0;
	virtual const Vector2D& GetVelocity() const = 0;
	virtual void SetMaxVelocity(float velocityMax) = 0;

	virtual void ApplyForce(const Vector2D& force, eForceType forceType) = 0;
	virtual void EnableGravity(bool enableGravity = true) = 0;
};