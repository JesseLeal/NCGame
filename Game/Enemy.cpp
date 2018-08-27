#include "Enemy.h"
#include "SpriteComponent.h"
#include "EnemyAIComponent.h"
#include "KinematicComponent.h"
#include "Renderer.h"
#include "AabbComponent.h"
#include "AudioSystem.h"
#include "EventManager.h"
#include "Explosion.h"
#include "AnimationComponent.h"
#include "WaypointControllerComponent.h"
#include "TransformControllerComponent.h"
#include "Timer.h"

std::vector<Vector2D> Enemy::m_enterPath = { Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f) };

void Enemy::Create(const Info & info)
{
	SetTag("enemy");

	m_info = info;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	m_transform.position = (m_info.side == LEFT) ? Vector2D(-64.0f, 400.0f) : Vector2D(864.0f, 400.0f);

	SpriteComponent* spriteComp = AddComponent<SpriteComponent>();
	spriteComp->Create("enemy01A.png", Vector2D(0.5f, 0.5f));
	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);
	AABBComponent* aabb = AddComponent<AABBComponent>();
	aabb->Create(Vector2D(0.8f, 0.9f));
	AnimationComponent* animation = AddComponent<AnimationComponent>();
	std::vector<std::string> textureNames;
	if (m_info.type == BEE)
		textureNames = { "enemy02A.png", "enemy02B.png" };
	else if (m_info.type == BOSS)
		textureNames = { "enemy01A.png", "enemy01B.png" };
	animation->Create(textureNames, 0.5f, AnimationComponent::LOOP);

	m_stateMachine = new StateMachine(GetScene(), this);
	m_stateMachine->AddState("EnterPath", new EnterPathState(m_stateMachine));
	m_stateMachine->AddState("EnterFormation", new EnterFormationState(m_stateMachine));
	m_stateMachine->AddState("Idle", new IdleState(m_stateMachine));
	m_stateMachine->AddState("Attack", new AttackState(m_stateMachine));
	m_stateMachine->SetState("EnterPath");
}

void Enemy::Update()
{
	Entity::Update();
	m_stateMachine->Update();
}

void Enemy::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "playermissile")
		{
			Explosion* explosion = m_scene->AddEntity<Explosion>();
			explosion->Create(m_transform.position);

			SetState(Entity::DESTROY);
			Event _event;
			_event.eventID = "add_score";
			_event.variant.asInt = 100;
			_event.variant.type = Variant::INTEGER;
			EventManager::Instance()->SendGameMessage(_event);
		}
	}
}

void EnterPathState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetOwner()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_owner->GetOwner<Enemy>()->m_info.speed, Enemy::m_enterPath);
}

void EnterPathState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetOwner()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetOwner()->RemoveComponent(waypointController);

		m_owner->SetState("EnterFormation");
	}
}

void EnterPathState::Exit()
{

}

void EnterFormationState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetOwner()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_owner->GetOwner<Enemy>()->m_info.speed, std::vector<Vector2D> { m_owner->GetOwner<Enemy>()->m_info.target } );
}

void EnterFormationState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetOwner()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetOwner()->RemoveComponent(waypointController);

		m_owner->SetState("Idle");
	}
}

void EnterFormationState::Exit()
{

}

void IdleState::Enter()
{
	TransformControllerComponent* transformComp = m_owner->GetOwner()->AddComponent<TransformControllerComponent>();
	transformComp->Create(m_owner->GetOwner<Enemy>()->m_info.target, 180.0f, 5.0f, m_owner->GetOwner<Enemy>()->m_info.speed);

	m_timer = Math::GetRandomRange(m_timeMin, m_timeMax);
}

void IdleState::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	m_timer -= dt;
	if (m_timer <= 0.0f)
	{
		m_owner->GetOwner()->RemoveComponent(m_owner->GetOwner()->GetComponent<TransformControllerComponent>());
		m_owner->SetState("Attack");
	}
}

void IdleState::Exit()
{

}

void AttackState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetOwner()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_owner->GetOwner<Enemy>()->m_info.speed, Enemy::m_enterPath);
}

void AttackState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetOwner()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetOwner()->RemoveComponent(waypointController);

		m_owner->SetState("EnterFormation");
	}
}

void AttackState::Exit()
{
	m_owner->GetOwner()->GetTransform().position.y = -64.0f;
}