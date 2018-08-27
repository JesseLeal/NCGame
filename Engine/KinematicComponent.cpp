#include "KinematicComponent.h"
#include "Timer.h"
#include "Physics.h"

void KinematicComponent::Create(float maxVel, float dampening, bool grav)
{
	m_maxVelocity = maxVel;
	m_dampening = dampening;
	m_enableGrav = grav;

	m_forceType = eForceType::FORCE;
	m_force = Vector2D::zero;
	m_velocity = Vector2D::zero;
}

void KinematicComponent::Destroy()
{
	//
}

void KinematicComponent::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	Vector2D force = (m_enableGrav) ? m_force + Physics::Instance()->GetGravity() : m_force;

	m_velocity += (m_force * dt);
	float magnitude = m_velocity.Length();
	if (magnitude > m_maxVelocity)
	{
		m_velocity = m_velocity.Normalized() * m_maxVelocity;
	}

	m_owner->GetTransform().position = m_owner->GetTransform().position + (m_velocity * dt);
	m_velocity = m_velocity * pow(m_dampening, dt);

	if (m_forceType == eForceType::IMPULSE)
	{
		m_force = Vector2D::zero;
	}
}

void KinematicComponent::ApplyForce(const Vector2D & force, eForceType forceType)
{
	m_forceType = forceType;
	switch (m_forceType) //treat force and impulse the same here
	{
	case FORCE:
	case IMPULSE:
		m_force = force;
		break;
	case VELOCITY:
		m_force = Vector2D::zero;
		m_velocity = force;
		break;
	}
}