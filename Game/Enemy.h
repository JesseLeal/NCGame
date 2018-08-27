#pragma once
#include "Entity.h"
#include "Vector2D.h"
#include "State.h"
#include "StateMachine.h"

class Enemy : public Entity
{
public:
	enum eType
	{
		BEE,
		BOSS
	};

	enum eSide
	{
		LEFT,
		RIGHT
	};

	struct Info
	{
		eType type;
		eSide side;
		float speed;
		Vector2D target;
	};

public:
	Enemy(Scene* scene, const ID& id = ID()) : Entity(scene, id) {}
	~Enemy() {}

	void Create(const Info& info);
	void Update();

	void OnEvent(const Event& event);

	static std::vector<Vector2D> m_enterPath;
	Info m_info;

protected:
	StateMachine * m_stateMachine;
};

class EnterPathState : public IState
{
public:
	EnterPathState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};

class EnterFormationState : public IState
{
public:
	EnterFormationState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};

class IdleState : public IState
{
public:
	IdleState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	float m_timeMin = 2.0f;
	float m_timeMax = 4.0f;
	float m_timer = 0.0f;
};

class AttackState : public IState
{
public:
	AttackState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};