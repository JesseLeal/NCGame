#pragma once
#include "Engine.h"
#include "Object.h"
#include "Component.h"
#include "Scene.h"
#include "Transform.h"
#include "Event.h"
#include "EventReciever.h"
#include <vector>
#include <cassert>

class Component;
class Scene;

class ENGINE_API Entity : public Object, public EventReceiver
{
public:
	enum eState
	{
		INACTIVE,
		ACTIVE,
		DESTROY
	};

public:
	Entity(Scene* scene, const ID& id = ID()) : m_scene(scene), Object(id) {}
	virtual ~Entity() {}

	virtual void Destroy();
	virtual void Update();
	virtual void Draw();

	virtual void OnEvent(const Event& event);

	template <typename T>
	T* AddComponent()
	{
		T* component = new T(this);
		assert(dynamic_cast<Component*>(component));
		m_components.push_back(component);

		return component;
	}

	void AddComponent(Component* comp);
	void RemoveComponent(Component* comp);

	bool Intersects(Entity* other);

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

	Scene* GetScene()
	{
		return m_scene;
	}
	void SetScene(Scene* scene)
	{
		m_scene = scene;
	}
	Transform& GetTransform()
	{
		return m_transform;
	}

	void SetState(eState state)
	{
		m_state = state;
	}
	eState GetState()
	{
		return m_state;
	}

	void SetTag(const ID& tag)
	{
		m_tag = tag;
	}
	const ID& GetTag()
	{
		return m_tag;
	}

protected:
	Transform m_transform;
	std::vector<Component*> m_components;
	Scene* m_scene;
	eState m_state = eState::ACTIVE;
	ID m_tag;
};