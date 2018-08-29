#include "EnemyAIComponent.h"
#include "KinematicComponent.h"
#include "Missile.h"
#include "AudioSystem.h"
#include "Timer.h"

void EnemyAIComponent::Create()
{
	m_cooldown = Math::GetRandomRange(m_firerateMin, m_firerateMax);
}

void EnemyAIComponent::Destroy()
{

}

void EnemyAIComponent::Update()
{
	m_cooldown -= Timer::Instance()->DeltaTime();

	if (m_cooldown <= 0.0f)
	{
		m_cooldown = Math::GetRandomRange(m_firerateMin, m_firerateMax);
		Missile* missile = new Missile(m_owner->GetScene());
		missile->Create(m_owner->GetTransform().position, Vector2D::up, 600.0f, "enemymissile");
		m_owner->GetScene()->AddEntity(missile);
		AudioSystem::Instance()->PlaySound("laser", false);
	}
}