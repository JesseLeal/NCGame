#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix33.h"
#include "RenderComponent.h"

class Texture;

class ENGINE_API SpriteComponent : public IRenderComponent
{
public:
	SpriteComponent(Entity* owner) : IRenderComponent(owner) {}

	void Create(const std::string& textureName, const Vector2D origin = Vector2D(0.0f, 0.0f));
	void Destroy();
	void Update();

	void Draw();

	void SetTexture(Texture* texture)
	{
		m_texture = texture;
	}
	Texture* GetTexture()
	{
		return m_texture;
	}
	const Vector2D& GetOrigin()
	{
		return m_origin;
	}

protected:
	Texture* m_texture = nullptr;
	Vector2D m_origin;
	Vector2D m_uv1;
	Vector2D m_uv2;
};