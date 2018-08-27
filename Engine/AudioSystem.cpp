#include "AudioSystem.h"
#include "FileSystem.h"
#include <cassert>

bool AudioSystem::Initialize(Engine * engine)
{
	FMOD_RESULT result = FMOD::System_Create(&m_fmodSystem);
	assert(result == FMOD_OK);
	void* extraDriverData = nullptr;
	result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extraDriverData);

	return true;
}

void AudioSystem::Update()
{
	m_fmodSystem->update();
}

void AudioSystem::AddSound(const std::string & id, const std::string & audioname)
{
	if (m_sounds.find(id) == m_sounds.end())
	{
		FMOD::Sound* fmodsound = nullptr;
		std::string filename = FileSystem::Instance()->GetPathname() + audioname;
		FMOD_RESULT result = m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &fmodsound);

		if (result == FMOD_OK)
		{
			m_sounds[id] = fmodsound;
		}
	}
}

void AudioSystem::PlaySound(const std::string & id, bool loop)
{
	assert(m_sounds.find(id) != m_sounds.end());
	FMOD::Channel* channel;
	auto iter = m_sounds.find(id);
	if (iter != m_sounds.end())
	{
		FMOD::Sound* fmodsound = iter->second;
		FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		fmodsound->setMode(mode);
		FMOD_RESULT result = m_fmodSystem->playSound(fmodsound, 0, false, &channel);
		assert(result == FMOD_OK);
	}
}

void AudioSystem::RemoveSound(const std::string & id)
{
	assert(m_sounds.find(id) != m_sounds.end());
	auto iter = m_sounds.find(id);
	if (iter != m_sounds.end())
	{
		FMOD::Sound* fmodsound = iter->second;
		FMOD_RESULT result = fmodsound->release();
		assert(result == FMOD_OK);
		m_sounds.erase(iter);
	}
}

void AudioSystem::Shutdown()
{
	for (auto& sound : m_sounds)
	{
		sound.second->release();
	}
	m_sounds.clear();
	m_fmodSystem->close();
	m_fmodSystem->release();
}
