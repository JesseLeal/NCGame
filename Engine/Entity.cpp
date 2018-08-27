#include "Entity.h"
#include <cassert>
#include "RenderComponent.h"
#include "CollisionComponent.h"

void Entity::Destroy()
{
	for (Component* comp : m_components)
	{
		comp->Destroy();
		delete comp;
	}

	m_components.clear();
}

void Entity::Update()
{
	for (Component* comp : m_components)
	{
		comp->Update();
	}
}

void Entity::Draw()
{
	IRenderComponent* renderComp = GetComponent<IRenderComponent>();
	if (renderComp)
	{
		renderComp->Draw();
	}
}

void Entity::OnEvent(const Event & event)
{

}

void Entity::AddComponent(Component * comp)
{
	assert(comp);
	assert(std::find(m_components.begin(), m_components.end(), comp) == m_components.end());

	m_components.push_back(comp);
}

void Entity::RemoveComponent(Component * comp)
{
	auto iter = std::find(m_components.begin(), m_components.end(), comp);
	(*iter)->Destroy();
	delete *iter;
	m_components.erase(iter);
}

bool Entity::Intersects(Entity * other)
{
	bool intersects = false;

	ICollisionComponent* collA = GetComponent<ICollisionComponent>();
	ICollisionComponent* collB = other->GetComponent<ICollisionComponent>();

	if (collA && collB)
	{
		intersects = collA->Intersects(collB);
	}

	return intersects;
}