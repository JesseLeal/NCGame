#include "Entity.h"

void Entity::AddComponent(Component * comp)
{
	m_components.push_back(comp);
}

void Entity::RemoveComponent(Component * comp)
{
	//I dont fricking know, iterate, find, and delete it
}