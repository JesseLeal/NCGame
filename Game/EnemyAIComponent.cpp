#include "EnemyAIComponent.h"
#include "KinematicComponent.h"
#include "Missile.h"
#include "AudioSystem.h"
#include "Timer.h"

void EnemyAIComponent::Create(float speed)
{
	m_speed = speed;
	m_cooldown = Math::GetRandomRange(m_firerateMin, m_firerateMax);
}

void EnemyAIComponent::Destroy()
{

}

void EnemyAIComponent::Update()
{
	Vector2D force = Vector2D::up;
	m_cooldown -= Timer::Instance()->DeltaTime();

	Entity* player = m_owner->GetScene()->FindEntity("player");
	if (player)
	{
		float dx = player->GetTransform().position.x - m_owner->GetTransform().position.x;
		if (dx < -16.0f) force.x = -1.0f;
		else if (dx > 16.0f) force.x = 1.0f;
	}

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	if (m_cooldown <= 0.0f)
	{
		m_cooldown = Math::GetRandomRange(m_firerateMin, m_firerateMax);
		Missile* missile = new Missile(m_owner->GetScene());
		missile->Create(m_owner->GetTransform().position, Vector2D::up, 800.0f, "enemymissile");
		m_owner->GetScene()->AddEntity(missile);
		AudioSystem::Instance()->PlaySound("laser", false);
	}
}