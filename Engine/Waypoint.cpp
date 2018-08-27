#include "Waypoint.h"
#include "AabbComponent.h"

void Waypoint::Create(const Vector2D & position, const Vector2D & size, Entity * owner)
{
	m_owner = owner;
	m_transform.position = position;
	m_transform.scale = size;

	AABBComponent* aabb = AddComponent<AABBComponent>();
	aabb->Create();
}

void Waypoint::Update()
{
	Entity::Update();
}