#include "States.h"
#include "StateMachine.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "InputManager.h"
#include "Enemy.h"
#include "Formation.h"
#include "Timer.h"
#include "Ship.h"

void TitleState::Enter()
{
	Entity* entity = m_owner->GetScene()->AddEntity<Entity>("title");
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spritecomp = entity->AddComponent<SpriteComponent>();
	spritecomp->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spritecomp->SetDepth(100);

	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);

	m_credits = 0;
}

void TitleState::Update()
{
	if (InputManager::Instance()->GetActionButton("start") == InputManager::eButtonState::PRESSED)
	{
		m_owner->SetState("enterstage");
	}
}

void TitleState::Exit()
{
	Entity* entity = m_owner->GetScene()->FindEntity("title");
	if (entity)
	{
		entity->SetState(Entity::DESTROY);
	}
}

void EnterStageState::Enter()
{
	//Timer::Instance()->Reset();
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->FindEntity("formation"));
	if (formation == nullptr)
	{
		formation = m_owner->GetScene()->AddEntity<Formation>("formation");
		formation->Create();
	}
}

void EnterStageState::Update()
{
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->FindEntity("formation"));
	formation->Update();

	Entity* ship = m_owner->GetScene()->FindEntity("player");
	if (ship == nullptr)
	{
		m_timer += Timer::Instance()->DeltaTime();
		if (m_timer >= m_respawnTimer)//&& the player has lives left
		{
			Ship* newShip = new Ship(m_owner->GetScene(), "player");
			newShip->Create(Vector2D(400.0f, 500.0f));
			m_owner->GetScene()->AddEntity(newShip);

			m_timer = 0.0f;
		}
		if (m_timer >= m_gameOverTimer)
		{
			//show a game over
		}
		if (m_timer >= m_resetTimer)
		{
			//get back to title screen
		}
	}
}

void EnterStageState::Exit()
{
	
}

void GameState::Enter()
{
	
}

void GameState::Update()
{
	
}

void GameState::Exit()
{
	
}