#include "Engine.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "AudioSystem.h"
#include <cassert>
#include "vector2D.h"
#include "matrix22.h"
#include "Timer.h"
#include <iostream>
#include "Text.h"
#include "TextManager.h"
#include "Physics.h"
#include "FileSystem.h"

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Thank You So Much-a For Playing My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	FileSystem::Instance()->Initialize(this);
	Physics::Instance()->Initialize(this);
	Timer::Instance()->Initialize(this);
	Renderer::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	TextManager::Instance()->Initialize(this);
	AudioSystem::Instance()->Initialize(this);
	InputManager::Instance()->Initialize(this);

	return true;
}

void Engine::Update()
{
	Timer::Instance()->Update();
	//Timer::Instance()->SetTimeScale(1.0f);
	InputManager::Instance()->Update();
	AudioSystem::Instance()->Update();
	Physics::Instance()->Update();
	FileSystem::Instance()->Update();

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		m_isQuit = true;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_isQuit = true;
		}
	}

	SDL_PumpEvents();

	if (InputManager::Instance()->GetButtonState(SDL_SCANCODE_GRAVE) == InputManager::eButtonState::PRESSED)
	{
		m_isDebug = !m_isDebug;
	}
}

void Engine::Shutdown()
{
	Timer::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	TextManager::Instance()->Shutdown();

	//AudioSystem::Instance()->RemoveSound("oof");

	AudioSystem::Instance()->Shutdown();
	Physics::Instance()->Shutdown();
	FileSystem::Instance()->Shutdown();

	SDL_DestroyRenderer(m_renderer);//move this
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}