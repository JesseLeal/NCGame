#pragma once
#include "Singleton.h"
#include "engine.h"

class AudioSystem : public Singleton<AudioSystem>
{
public:
	AudioSystem() {}

	~AudioSystem() {}

	bool Initialize(Engine* engine);

	void Shutdown();
};