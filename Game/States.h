#pragma once
#include "state.h"

class TitleState : public IState
{
public:
	TitleState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	size_t m_credits = 0;
};

class EnterStageState : public IState
{
public:
	EnterStageState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	float m_gameOverTimer = 3.0f;
	float m_resetTimer = 6.0f;
	float m_respawnTimer = 2.0f;
	float m_timer = 0.0f;
};

class GameState : public IState
{
public:
	GameState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};