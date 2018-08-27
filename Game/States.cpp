#include "States.h"
#include "StateMachine.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "InputManager.h"
#include "Enemy.h"

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
		m_owner->SetState("game");
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

void GameState::Enter()
{
	std::vector<Enemy::Info> squadron =
	{	{ Enemy::eType::BEE, Enemy::eSide::LEFT, 400.0f, Vector2D(100.0f, 100.0f) },
		{ Enemy::eType::BEE, Enemy::eSide::RIGHT, 400.0f, Vector2D(180.0f, 100.0f) },
		{ Enemy::eType::BOSS, Enemy::eSide::LEFT, 400.0f, Vector2D(260.0f, 100.0f) },
		{ Enemy::eType::BEE, Enemy::eSide::RIGHT, 400.0f, Vector2D(400.0f, 100.0f) },
		{ Enemy::eType::BEE, Enemy::eSide::LEFT, 400.0f, Vector2D(340.0f, 100.0f) },
	};
	for (Enemy::Info info : squadron)
	{
		Enemy* enemy = new Enemy(m_owner->GetScene());
		enemy->Create(info);
		m_owner->GetScene()->AddEntity(enemy);
	}
}

void GameState::Update()
{

}

void GameState::Exit()
{
	//destroy the universe
}