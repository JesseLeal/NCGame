#pragma once
#include "Engine.h"
#include "Object.h"
#include "Entity.h"

class Entity;

class ENGINE_API Component : public Object
{
public:
	Component(Entity* owner, const ID& id = ID()) : m_owner(owner), Object(id) {}

	virtual void Update() = 0;
	virtual void Destroy() = 0;

	Entity* GetOwner()
	{
		return m_owner;
	}

protected:
	Entity * m_owner = nullptr;
};