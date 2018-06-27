#pragma once
#include <iostream>
#include "SDL.h"

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

class ENGINE_API Engine
{
public:
	Engine() { }
	~Engine() {}

	bool Initialize();
	void Update();
	void Shutdown();

	bool isQuit()
	{
		return m_isQuit;
	}

	void Display()
	{
		std::cout << "Hello World!" << std::endl;
	}

protected:
	bool m_isQuit = false;
	SDL_Window * m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};
