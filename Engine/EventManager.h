#pragma once
#include "Singleton.h"
#include "Engine.h"
#include "Event.h"
#include "EventReciever.h"

class ENGINE_API EventManager : public Singleton<EventManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void SendMessage(const Event& event);
	void SendGameMessage(const Event& event);

	void SetGameEventReceiver(EventReceiver* eventRec)
	{
		m_gameEventReceiver = eventRec;
	}

protected:
	friend Singleton<EventManager>;

protected:
	Engine * m_engine;
	EventReceiver* m_gameEventReceiver = nullptr;
};