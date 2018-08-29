#include "ShipControllerComponent.h"
#include "InputManager.h"
#include "Timer.h"
#include "KinematicComponent.h"
#include "Ship.h"
#include "Missile.h"
#include "AudioSystem.h"

void ShipControllerComponent::Create(float speed)
{
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("fire", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);

	m_speed = speed;
	m_cooldown = 0.0f;
}

void ShipControllerComponent::Destroy()
{

}

void ShipControllerComponent::Update()
{
	m_cooldown -= Timer::Instance()->DeltaTime();
	Vector2D force = Vector2D::zero;
	if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) || (InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD))
	{
		force += Vector2D::left;
	}
	if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) || (InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD))
	{
		force += Vector2D::right;
	}

	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	{
		std::vector<Entity*> missiles = m_owner->GetScene()->GetEntitiesWithTag("playermissile");
		if (missiles.size() < 4)
		{
			Missile* missile = new Missile(m_owner->GetScene());
			missile->Create(m_owner->GetTransform().position, Vector2D::down, 1000.0f, "playermissile");
			m_owner->GetScene()->AddEntity(missile);
			AudioSystem::Instance()->PlaySound("laser", false);
		}
	}

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}
}
