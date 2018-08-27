#include "Ship.h"
#include "SpriteComponent.h"
#include "ShipControllerComponent.h"
#include "KinematicComponent.h"
#include "Renderer.h"
#include "AabbComponent.h"
#include "AudioSystem.h"

void Ship::Create(const Vector2D & position)
{
	SetTag("player");

	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SpriteComponent* spriteComp = AddComponent<SpriteComponent>();
	spriteComp->Create("ship.png", Vector2D(0.5f, 0.5f));
	ShipControllerComponent* shipComp = AddComponent<ShipControllerComponent>();
	shipComp->Create(800.0f);
	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);
	AABBComponent* aabb = AddComponent<AABBComponent>();
	aabb->Create();

	AudioSystem::Instance()->AddSound("laser", "laser.wav");
	AudioSystem::Instance()->AddSound("shipExplode", "ship-explosion.wav");
}

void Ship::Update()
{
	Entity::Update();

	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 20.0f, (size.x - 20.0f));
}

void Ship::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "enemy" || event.sender->GetTag() == "enemymissile")
		{
			AudioSystem::Instance()->PlaySound("shipExplode", false);
			SetState(Entity::DESTROY);
		}
	}
}