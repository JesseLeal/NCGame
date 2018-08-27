#include "EventManager.h"
#include "Entity.h"

bool EventManager::Initialize(Engine * engine)
{
	m_engine = engine;

	return true;
}

void EventManager::Shutdown()
{

}

void EventManager::Update()
{

}

void EventManager::SendMessage(const Event & event)
{
	event.reciever->OnEvent(event);
}

void EventManager::SendGameMessage(const Event & event)
{
	m_gameEventReceiver->OnEvent(event);
}