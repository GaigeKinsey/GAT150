#include "engine.h"
#include "scene.h"
#include "..\\core\filesystem.h"
#include "..\\core\name.h"

#include <iostream>

bool Engine::Startup()
{
	Name::AllocNames();
	filesystem::set_current_path("../");

	AudioSystem* audioSystem = new AudioSystem(this);
	audioSystem->Startup();
	m_systems.push_back(audioSystem);

	Renderer* renderer = new Renderer(this);
	renderer->Startup();
	renderer->Create("game", 800, 600);
	m_systems.push_back(renderer);

	m_resource_manager = new ResourceManager<Resource>(renderer);

	EntityEventDispatcher* dispatcher = new EntityEventDispatcher(this);
	dispatcher->Startup();
	m_systems.push_back(dispatcher);

	m_scene = new Scene();
	m_scene->Create("scene", this);

	rapidjson::Document document;
	json::load("scenes/scene.txt", document);
	m_scene->Load(document);
	m_scene->Initialize();

	return true;
}

void Engine::Shutdown()
{
	m_resource_manager->RemoveAll();
	delete m_resource_manager;

	for (System* system : m_systems) {
		system->Shutdown();
		delete system;
	}
	m_systems.clear();


	m_scene->Destroy();
	delete m_scene;

	Name::FreeNames();

	SDL_Quit();
}

void Engine::Update()
{
	g_timer.tick();

	SDL_Event e;
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_quit = true;
		}
	}

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	if (keyboardState[SDL_SCANCODE_ESCAPE]) m_quit = true;

	for (System* system : m_systems) {
		system->Update();
	}
	m_scene->Update();

	GetSystem<Renderer>()->BeginFrame();
	m_scene->Draw();
	GetSystem<Renderer>()->EndFrame();
}
