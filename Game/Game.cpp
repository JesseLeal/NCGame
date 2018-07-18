#include "Game.h"
#include "Engine.h"
#include "InputManager.h"
#include "AudioSystem.h"
#include "Text.h"
#include "TextManager.h"
#include "Renderer.h"
#include "TextureManager.h"
#include "Timer.h"
#include <iostream>
#include "matrix22.h"

Vector2D position(400.0f, 300.0f);
float angle = 0.0f;
Text* text;

bool Game::Initialize()
{
	bool success = m_engine->Initialize();

	InputManager::Instance()->AddAction("fire", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("steer", InputManager::eAxis::X, InputManager::eDevice::MOUSE);

	AudioSystem::Instance()->AddSound("oof", "..\\Content\\oof.wav");

	text = TextManager::Instance()->CreateText("", "..\\Content\\jokerman.TTF", 30, Color::red);

	m_running = true;

	return success;
}

void Game::Shutdown()
{
	m_engine->Shutdown();
}

void Game::Update()
{
	m_running = !m_engine->isQuit();
	m_engine->Update();

	int x, y;
	SDL_GetMouseState(&x, &y);

	if (InputManager::Instance()->GetNumControllers() > 0)
	{
		if (InputManager::Instance()->GetButtonState(SDL_CONTROLLER_BUTTON_A, InputManager::eDevice::CONTROLLER) == InputManager::eButtonState::PRESSED)
		{
		std::cout << "An a press is an a press, you can't say it's only a half" << std::endl;
		}
	}
	
	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	{
		std::cout << "pew pew" << std::endl;
		AudioSystem::Instance()->PlaySound("oof", false);
	}

	float steer = InputManager::Instance()->GetActionAxisRelative("steer");
	angle += (steer * 360.0f) * Timer::Instance()->DeltaTime();

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