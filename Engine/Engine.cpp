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

Vector2D position(400.0f, 300.0f);
float angle = 0.0f;
Text* text;

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Thank You So Much-a For Playing My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	Timer::Instance()->Initialize(this);
	Renderer::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	TextManager::Instance()->Initialize(this);
	AudioSystem::Instance()->Initialize(this);
	InputManager::Instance()->Initialize(this);

	InputManager::Instance()->AddAction("fire", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("steer", InputManager::eAxis::X, InputManager::eDevice::MOUSE);
	InputManager::Instance()->AddAction("DashDance", SDL_CONTROLLER_AXIS_LEFTX, InputManager::eDevice::CONTROLLER);

	text = TextManager::Instance()->CreateText("", "..\\Content\\jokerman.TTF", 20, Color::red);

	return true;
}

void Engine::Update()
{
	Timer::Instance()->Update();
	//Timer::Instance()->SetTimeScale(5.0f);

	InputManager::Instance()->Update();

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

	int x, y;
	SDL_GetMouseState(&x, &y);


	if (InputManager::Instance()->GetButtonState(SDL_CONTROLLER_BUTTON_A, InputManager::eDevice::CONTROLLER) == InputManager::eButtonState::PRESSED)
	{
		std::cout << "An a press is an a press, you can't say it's only a half" << std::endl;
	}
	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	{
		std::cout << "gun" << std::endl;
	}
	if (InputManager::Instance()->GetAxisAbsolute(SDL_CONTROLLER_AXIS_LEFTX, InputManager::eDevice::CONTROLLER) == 0.0f)
	{
		std::cout << "DASHU" << std::endl;
	}
	if (InputManager::Instance()->GetAxisAbsolute(SDL_CONTROLLER_AXIS_LEFTX, InputManager::eDevice::CONTROLLER) == 1.0f)
	{
		std::cout << "DANCEU" << std::endl;
	}

	float steer = InputManager::Instance()->GetActionAxisRelative("steer");
	angle += (steer * 20.0f) * Timer::Instance()->DeltaTime();

	Vector2D force = Vector2D::zero;

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	if (keystate[SDL_SCANCODE_LEFT])
		angle -= 180.0f * Timer::Instance()->DeltaTime();
	if (keystate[SDL_SCANCODE_RIGHT])
		angle += 180.0f * Timer::Instance()->DeltaTime();
	if (keystate[SDL_SCANCODE_DOWN])
		force.y += 0.5f;
	if (keystate[SDL_SCANCODE_UP])
		force.y += -0.5f;

	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position = position + force;

	if (position.x > 800)
		position.x = 0;
	if (position.x < 0)
		position.x = 800;
	if (position.y > 600)
		position.y = 0;
	if (position.y < 0)
		position.y = 600;


	Renderer::Instance()->BeginFrame();

	SDL_Texture* texture = TextureManager::Instance()->getTexture("..\\content\\car.bmp");

	Renderer::Instance()->SetColor(Color::black);
	Renderer::Instance()->DrawTexture(texture, position, angle);

	std::vector<Color> colors = { Color::red, Color::white, Color::green, Color::yellow };
	text->SetText("Way past cool", colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);

	Renderer::Instance()->EndFrame();

	//SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	//SDL_RenderClear(m_renderer);

	//SDL_Rect rect = {x, y, 64, 64};

	//SDL_Texture* texture = TextureManager::Instance()->getTexture("..\\content\\cat.bmp");
	//
	//SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	//SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255);
	////SDL_RenderFillRect(m_renderer, &rect);
	////SDL_RenderCopy(m_renderer, m_texture, nullptr, &rect);
	//SDL_RenderCopyEx(m_renderer, texture, nullptr, &rect, 120.0, nullptr, SDL_FLIP_NONE);

	//SDL_RenderPresent(m_renderer);
}

void Engine::Shutdown()
{
	Timer::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	TextManager::Instance()->Shutdown();
	AudioSystem::Instance()->Shutdown();


	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}