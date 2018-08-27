#pragma once
#include "Singleton.h"
#include "Engine.h"
#include "Vector2D.h"
#include <vector>
#include <map>

class ENGINE_API InputManager : public Singleton<InputManager>
{
public:
	enum eButtonState
	{
		IDLE,
		PRESSED,
		HELD,
		RELEASED
	};

	enum eDevice
	{
		KEYBOARD,
		MOUSE,
		CONTROLLER
	};

	enum eAxis
	{
		X,
		Y
	};

	struct InputInfo
	{
		int id;
		eDevice device;
		int index;
	};

	struct ControllerInfo
	{
		SDL_GameController* controller;

		Uint8 buttonState[SDL_CONTROLLER_BUTTON_MAX];
		Uint8 prevButtonState[SDL_CONTROLLER_BUTTON_MAX];
		float axis[SDL_CONTROLLER_AXIS_MAX];
		float prevAxis[SDL_CONTROLLER_AXIS_MAX];
	};

public:
	InputManager() {}

	~InputManager() {}

	bool Initialize(Engine* engine);
	void Update();
	void Shutdown();

	void AddAction(const std::string& action, int id, eDevice device, int index = 0);
	eButtonState GetActionButton(const std::string& action);
	float GetActionAxisAbsolute(const std::string& action);
	float GetActionAxisRelative(const std::string& action);

	float GetAxisAbsolute(int id, eDevice device = eDevice::MOUSE, int index = 0);
	float GetAxisRelative(int id, eDevice device = eDevice::MOUSE, int index = 0);

	eButtonState GetButtonState(int id, eDevice device = eDevice::KEYBOARD, int index = 0);

	int GetNumControllers();
	
protected:
	bool GetButtonDown(int id, eDevice device, int index = 0);
	bool GetPrevButtonDown(int id, eDevice device, int index = 0);

private:
	Engine * m_engine;

	Uint8* m_prevKeystate;
	Uint8* m_keystate;
	int m_numKeys;

	Uint8 m_mouseButtonstate;
	Uint8 m_prevMouseButtonstate;
	Vector2D m_mousePosition;
	Vector2D m_prevMousePosition;

	std::vector<ControllerInfo> m_controllers;
	std::map<std::string, InputInfo> m_actions;
};