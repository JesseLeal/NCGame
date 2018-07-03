#pragma once
#include "Singleton.h"
#include "engine.h"
#include "color.h"
#include "vector2D.h"

class Renderer : public Singleton<Renderer>
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

	friend Singleton<Renderer>;

private:
	Engine * m_engine;
	SDL_Renderer* m_renderer = nullptr;
};