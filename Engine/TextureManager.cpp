#include "TextureManager.h"
#include "Renderer.h"
#include <cassert>

TextureManager* TextureManager::m_instance = nullptr;

bool TextureManager::Initialize(Engine * engine)
{
	m_engine = engine;
	return true;
}

void TextureManager::Shutdown()
{
	for (auto texture : m_textures)
	{
		SDL_DestroyTexture(texture.second);
	}
}

SDL_Texture * TextureManager::getTexture(const std::string & textureName)
{
	SDL_Texture* texture = m_textures[textureName];

	if (texture == nullptr)
	{
		SDL_Surface* surface = SDL_LoadBMP(textureName.c_str());
		assert(surface);
		texture = SDL_CreateTextureFromSurface(Renderer::Instance()->GetRenderer(), surface);
		SDL_FreeSurface(surface);

		m_textures[textureName] = texture;
	}
	

	return texture;
}
