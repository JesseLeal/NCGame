#pragma once
#include "Singleton.h"
#include "Engine.h"

class ENGINE_API Timer : public Singleton<Timer>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	float DeltaTime()
	{
		return m_dt * m_timeScale;
	}
	float UnscaledDeltaTime()
	{
		return m_dt;
	}

	void SetTimeScale(float ts)
	{
		m_timeScale = ts;
	}
	float GetTimeScale() const
	{
		return m_timeScale;
	}

	void Pause()
	{
		m_paused = true;
	}
	void Unpause()
	{
		m_paused = false;
	}
	bool IsPaused() const
	{
		return m_paused;
	}

	void Reset();

	friend Singleton<Timer>;

protected:
	Timer() {}

private:
	Engine * m_engine;
	float m_dt;
	Uint32 m_prevTicks;
	bool m_paused = false;
	float m_timeScale = 1.0f;
};

