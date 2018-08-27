#pragma once
#include "EventReciever.h"

class Engine;
class Scene;
class StateMachine;

class Game : public EventReceiver
{
public:
	Game(Engine* engine) : m_engine(engine) {}
	~Game() {}

	bool Initialize();
	void Shutdown();
	void Update();

	bool Run() { return m_running; }

	void OnEvent(const Event& event);

protected:
	bool m_running = false;
	Engine* m_engine = nullptr;
	Scene* m_scene = nullptr;
	int m_score = 0;
	StateMachine* m_stateMachine = nullptr;
};