#pragma once
#include "Singleton.h"
#include "engine.h"

class InputManager : public Singleton<InputManager>
{
public:
	InputManager() {}

	~InputManager() {}

	bool Initialize(Engine* engine);

	void Shutdown();
};