#include "engine.h"
#include "..\\core\filesystem.h"

bool Engine::Startup()
{
	filesystem::set_current_path("../");

	m_audioSystem = new AudioSystem(this);
	m_audioSystem->Startup();

	m_renderer = new Renderer(this);
	m_renderer->Startup();
	m_renderer->CreateWindow("game", 800, 600);

	return true;
}

void Engine::Shutdown()
{
	m_renderer->Shutdown();
	delete m_renderer;

	m_audioSystem->Shutdown();
	delete m_audioSystem;

	SDL_Quit();
}

void Engine::Update()
{
	m_audioSystem->Update();
	m_renderer->Update();
}
