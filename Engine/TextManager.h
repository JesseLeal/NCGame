#pragma once

#include "Engine.h"
#include "Singleton.h"
#include "Color.h"
#include "Vector2D.h"
#include "Text.h"
#include <string>
#include <vector>

class ENGINE_API TextManager : public Singleton<TextManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

	Text* CreateText(const std::string& text, const std::string& fontName, int size, const Color& color);
	void DestroyText(Text* text);

	friend Singleton<TextManager>;

protected:
	TextManager() {}

private:
	Engine * m_engine;
	std::vector<Text*> m_texts;
};