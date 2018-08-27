#include "AnimationComponent.h"
#include "Timer.h"
#include "SpriteComponent.h"

void AnimationComponent::Create(const std::vector<std::string>& textureNames, float rate, ePlayback playback)
{
	for (std::string text : textureNames)
	{
		Texture* texture = new Texture();
		texture->Create(text);
		m_textures.push_back(texture);
	}

	m_rate = rate;
	m_playback = playback;
}

void AnimationComponent::Destroy()
{
	for (Texture* texture : m_textures)
	{
		texture->Destroy();
		delete texture;
	}
}

void AnimationComponent::Update()
{
	m_timer += Timer::Instance()->DeltaTime();
	if (m_timer >= m_rate)
	{
		m_timer -= m_rate;
		m_frame+= m_direction;
		if (m_frame >= (int) m_textures.size() || m_frame < 0)
		{
			switch (m_playback)
			{
			case LOOP:
				m_frame = 0;
				break;
			case ONE_TIME:
				m_frame = (int) m_textures.size() - 1;
				break;
			case ONE_TIME_DESTROY:
				m_frame = (int) m_textures.size() - 1; // maybe not needed?
				m_owner->SetState(Entity::DESTROY);
				break;
			case PING_PONG:
				//m_frame = Math::Clamp(m_frame, 0.0f, m_textures.size() - 1);
				m_direction = -m_direction;
				break;
			}
		}
	}

	SpriteComponent* spriteComp = m_owner->GetComponent<SpriteComponent>();
	if (spriteComp)
	{
		spriteComp->SetTexture(GetTexture());
	}
}

Texture * AnimationComponent::GetTexture()
{
	return m_textures[m_frame];
}