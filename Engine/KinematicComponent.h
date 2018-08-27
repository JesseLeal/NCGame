#pragma once
#include "PhysicsComponent.h"

class ENGINE_API KinematicComponent : public IPhysicsComponent
{
public:
	KinematicComponent(Entity* owner) : IPhysicsComponent(owner) {}

	void Create(float maxVel = 500.0f, float dampening = 1.0f, bool grav = false);
	void Destroy();
	void Update();

	void SetVelocity(const Vector2D& velocity)
	{
		m_velocity = velocity;
	}
	const Vector2D& GetVelocity() const
	{
		return m_velocity;
	}
	void SetMaxVelocity(float velocityMax)
	{
		m_maxVelocity = velocityMax;
	}

	void ApplyForce(const Vector2D& force, eForceType forceType);
	void EnableGravity(bool enableGravity = true)
	{
		m_enableGrav = enableGravity;
	}

protected:
	bool m_enableGrav = false;
	float m_dampening = 1.0f;

	eForceType m_forceType;
	Vector2D m_velocity;
	float m_maxVelocity;
	Vector2D m_force;
};