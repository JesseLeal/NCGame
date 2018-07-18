#pragma once
#include "Engine.h"
#include "Object.h"
#include "Component.h"
#include <vector>

class Component;

class ENGINE_API Entity : public Object
{
public:
	Entity(const ID& id = ID()) : Object(id) {}
	virtual ~Entity() {}

	void AddComponent(Component* comp);
	void RemoveComponent(Component* comp);

	template <typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* _component : m_components)
		{
			component = dynamic_cast<T*>(_component);
			if (component != nullptr)
				break;
		}
		return component;
	}

protected:
	std::vector<Component*> m_components;
};