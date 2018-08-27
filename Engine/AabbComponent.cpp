#include "AabbComponent.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "DebugDraw.h"

void AABBComponent::Create(const Vector2D& offset)
{
	m_offset = offset;
}

void AABBComponent::Destroy()
{
	//
}

void AABBComponent::Update()
{
	Transform transform = m_owner->GetTransform();
	Vector2D position = transform.position;
	Vector2D size = transform.scale * m_offset;

	SpriteComponent* spritecomp = m_owner->GetComponent<SpriteComponent>();
	if (spritecomp)
	{
		size = size * spritecomp->GetTexture()->GetSize();
		position = position + (size) * (Vector2D(0.5f, 0.5f) - spritecomp->GetOrigin());
	}

	m_aabb.Build(position, size * 0.5f);

	DEBUG_DRAW_AABB(m_aabb, Color::blue);
}

bool AABBComponent::Intersects(ICollisionComponent * other)
{
	bool intersects = false;
	AABBComponent* aabbcomp = dynamic_cast<AABBComponent*>(other);
	if (aabbcomp)
	{
		intersects = m_aabb.Intersects(aabbcomp->m_aabb);
	}

	return intersects;
}