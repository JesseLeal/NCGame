#pragma once
#include "Engine.h"
#include "Event.h"

class ENGINE_API EventReceiver
{
public:
	EventReceiver() {}

	virtual void OnEvent(const Event& event) = 0;
};