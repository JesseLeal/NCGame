#include "Engine.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "AudioSystem.h"
#include <cassert>
#include "vector2D.h"
#include "matrix22.h"
#include "Timer.h"

//BUILD:
//InputManager
//Renderer
//AudioSystem

Vector2D position(400.0f, 300.0f);
float angle = 0.0f;

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Thank You So Much-a For Playing My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	Timer::Instance()->Initialize(this);
	Renderer::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	AudioSystem::Instance()->Initialize(this);

	return true;
}

void Engine::Update()
{
	Timer::Instance()->Update();
	//Timer::Instance()->SetTimeScale(5.0f);

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

	int x, y;
	SDL_GetMouseState(&x, &y);

	Vector2D force = Vector2D::zero;

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	if (keystate[SDL_SCANCODE_LEFT])
		angle -= 180.0f * Timer::Instance()->DeltaTime();
	if (keystate[SDL_SCANCODE_RIGHT])
		angle += 180.0f * Timer::Instance()->DeltaTime();
	if (keystate[SDL_SCANCODE_DOWN])
		force.y += 0.3f;
	if (keystate[SDL_SCANCODE_UP])
		force.y += -0.3f;

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
	TextureManager::Instance()->Shutdown();
	AudioSystem::Instance()->Shutdown();

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}