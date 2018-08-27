#pragma once
#include "State.h"
#include "Scene.h"
#include <map>

class ENGINE_API StateMachine
{
public:
	StateMachine(Scene* scene, Entity* owner = nullptr) : m_scene(scene), m_owner(owner) {}
	~StateMachine() {}

	void Update();

	void AddState(const std::string& stateName, IState* state);
	void SetState(const std::string& key);

	Scene* GetScene()
	{
		return m_scene;
	}
	Entity* GetOwner()
	{
		return m_owner;
	}

	template<typename T>
	T* GetOwner()
	{
		return dynamic_cast<T*>(m_owner);
	}

protected:
	Scene* m_scene = nullptr;
	Entity* m_owner = nullptr;
	IState* m_state = nullptr;
	std::map<std::string, IState*> m_states;
};