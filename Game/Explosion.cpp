#include "Explosion.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "AudioSystem.h"

void Explosion::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	SpriteComponent* spritecomp = AddComponent<SpriteComponent>();
	spritecomp->Create("", Vector2D(0.5f, 0.5f));
	AnimationComponent* animationComp = AddComponent<AnimationComponent>();
	std::vector<std::string> textureNames = { "enemy-explosion01.png", "enemy-explosion02.png", "enemy-explosion03.png", "enemy-explosion04.png", "enemy-explosion05.png" };
	animationComp->Create(textureNames, 0.1f, AnimationComponent::ONE_TIME_DESTROY);

	AudioSystem::Instance()->AddSound("explosion", "enemy-hit01.wav");
	AudioSystem::Instance()->PlaySound("explosion", false);
}

void Explosion::Update()
{
	Entity::Update();
}