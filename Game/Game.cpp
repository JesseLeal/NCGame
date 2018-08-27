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
#include "Entity.h"
#include "Scene.h"
#include "Ship.h"
#include "FileSystem.h"
#include "Enemy.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "EventManager.h"
#include "AnimationComponent.h"
#include "StateMachine.h"
#include "States.h"

bool Game::Initialize()
{
	bool success = m_engine->Initialize();

	FileSystem::Instance()->SetPathname("..\\content\\galaga\\");
	EventManager::Instance()->SetGameEventReceiver(this);

	m_scene = new Scene();
	m_stateMachine = new StateMachine(m_scene);
	m_stateMachine->AddState("title", new TitleState(m_stateMachine));
	m_stateMachine->AddState("game", new GameState(m_stateMachine));
	m_stateMachine->SetState("title");

	Entity* entity = new Entity(m_scene, "score");
	entity->GetTransform().position = Vector2D(20.0f, 20.0f);
	TextComponent* textcomp = entity->AddComponent<TextComponent>();
	textcomp->Create("00000", "emulogic.ttf", 18, Color::white);
	textcomp->SetDepth(100);
	m_scene->AddEntity(entity);

	Ship* ship = new Ship(m_scene, "player");
	ship->Create(Vector2D(400.0f, 500.0f));
	m_scene->AddEntity(ship);

	/*for (size_t i = 0; i < 10; i++)
	{
		Enemy* enemy = new Enemy(m_scene);
		float x = Math::GetRandomRange(200.0f, 600.0f);
		float y = Math::GetRandomRange(0.0f, 60.0f);
		enemy->Create(Vector2D(x, y));
		m_scene->AddEntity(enemy);
	}*/

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

	Entity* scoreEntity = m_scene->FindEntity("score");
	if (scoreEntity)
	{
		TextComponent* textComp = scoreEntity->GetComponent<TextComponent>();
		std::string score = std::to_string(m_score);
		while (score.length() < 5)
		{
			score = "0" + score;
		}
		textComp->SetText(score);
	}

	m_stateMachine->Update();
	Renderer::Instance()->SetColor(Color::black);
	Renderer::Instance()->BeginFrame();
	m_scene->Update();
	m_scene->Draw();
	Renderer::Instance()->EndFrame();
}

void Game::OnEvent(const Event & event)
{
	if (event.eventID == "add_score")
	{
		m_score += event.variant.asInt;
	}
}