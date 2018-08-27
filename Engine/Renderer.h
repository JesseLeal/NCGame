#pragma once
#include "Singleton.h"
#include "Engine.h"
#include "Color.h"
#include "Vector2D.h"
#include "Texture.h"
#include <SDL_image.h>

class ENGINE_API Renderer : public Singleton<Renderer>
{
public:
	Renderer() {}

	~Renderer() {}

	bool Initialize(Engine* engine);

	void Shutdown();

	SDL_Renderer* GetRenderer()
	{
		return m_renderer;
	}

	void BeginFrame();
	void EndFrame();

	void SetColor(const Color& color);
	void DrawTexture(SDL_Texture* texture, const Vector2D& position, float angle);
	void DrawTexture(SDL_Texture* texture, const Vector2D& position, const Vector2D& scale, float angle);
	void DrawTexture(Texture* texture, const Vector2D& position, const Vector2D& scale, float angle);
	void DebugDrawLine(const Vector2D& start, const Vector2D& end, const Color& color = Color::red);

	Vector2D GetSize();

	friend Singleton<Renderer>;

private:
	Engine * m_engine;
	SDL_Renderer* m_renderer = nullptr;
};