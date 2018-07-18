#pragma once

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif

#pragma warning(disable:4251)

#include "sdl.h"

class TextureManager;

class ENGINE_API Engine
{
public:
	Engine() { }
	~Engine() {}

	bool Initialize();
	void Update();
	void Shutdown();

	SDL_Window* getWindow()
	{
		return m_window;
	}

	bool isQuit()
	{
		return m_isQuit;
	}

protected:
	bool m_isQuit = false;
	SDL_Window * m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;
};
