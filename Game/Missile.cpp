#include "Missile.h"
#include "SpriteComponent.h"
#include "KinematicComponent.h"
#include "Timer.h"
#include "AabbComponent.h"

void Missile::Create(const Vector2D & position, const Vector2D & direction, float speed, const ID& tag)
{
	m_lifetime = 1.4f;
	SetTag(tag);

	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SpriteComponent* spriteComp = AddComponent<SpriteComponent>();
	if (tag == "playermissile")
		spriteComp->Create("missile01.png", Vector2D(0.5f, 0.5f));
	else if (tag == "enemymissile")
		spriteComp->Create("missile02.png", Vector2D(0.5f, 0.5f));
	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.9f);
	AABBComponent* aabb = AddComponent<AABBComponent>();
	aabb->Create(Vector2D(0.6f, 0.9f));

	kinematic->ApplyForce(direction * speed, KinematicComponent::FORCE);
}

void Missile::Update()
{
	Entity::Update();
	m_lifetime -= Timer::Instance()->DeltaTime();
	if (m_lifetime <= 0.0f)
	{
		SetState(Entity::DESTROY);
	}
}

void Missile::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (m_tag == "playermissile" && event.sender->GetTag() == "enemy")
		{
			SetState(Entity::DESTROY);
		}

		if (m_tag == "enemymissile" && event.sender->GetTag() == "player")
		{
			SetState(Entity::DESTROY);
		}
	}
}