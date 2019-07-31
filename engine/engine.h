#pragma once

#include "..\\renderer\renderer.h"
#include "..\\audio\audiosystem.h"

#include "system.h"

class Engine
{
public:
	Engine() {}
	~Engine() {}

	bool Startup();
	void Shutdown();
	void Update();

	Renderer* GetRenderer() { return m_renderer; }
	AudioSystem* GetAudioSystem() { return m_audioSystem; }

private:
	AudioSystem* m_audioSystem = nullptr;
	Renderer* m_renderer = nullptr;
};