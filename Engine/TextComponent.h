#pragma once
#include "RenderComponent.h"
#include "Text.h"

class ENGINE_API TextComponent : public IRenderComponent
{
public:
	TextComponent(Entity* owner) : IRenderComponent(owner) {}

	void Create(const std::string& text, const std::string& fontName, int fontSize, const Color& color, const Vector2D origin = Vector2D(0.0f, 0.0f));
	void Destroy();
	void Update();

	void Draw();

	const Vector2D& GetOrigin()
	{
		return m_origin;
	}

	void SetText(const std::string& text);
	void SetColor(const Color& color);

protected:
	Text * m_text = nullptr;
	Vector2D m_origin;
};