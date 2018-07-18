#pragma once
#include "Singleton.h"
#include "engine.h"
#include <string>
#include "fmod.hpp"
#include <map>

class ENGINE_API AudioSystem : public Singleton<AudioSystem>
{
public:
	AudioSystem() {}
	~AudioSystem() {}

	void AddSound(const std::string& id, const std::string& filename);
	void PlaySound(const std::string& id, bool loop);
	void RemoveSound(const std::string& id);

	bool Initialize(Engine* engine);
	void Update();
	void Shutdown();

private:
	FMOD::System* m_fmodSystem;
	std::map<std::string, FMOD::Sound*> m_sounds;
};