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

	InputSystem* input = new InputSystem(this);
	input->Startup();
	m_systems.push_back(input);

	m_resource_manager = new ResourceManager<Resource>(renderer);

	EntityEventDispatcher* dispatcher = new EntityEventDispatcher(this);
	dispatcher->Startup();
	m_systems.push_back(dispatcher);

	return true;
}

void Engine::Shutdown()
{
	DestroyScene();

	delete m_resource_manager;

	for (System* system : m_systems) {
		system->Shutdown();
		delete system;
	}
	m_systems.clear();

	Name::FreeNames();

	SDL_Quit();
}

void Engine::Update()
{
	SDL_Event e;
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_quit = true;
		}
	}

	g_timer.tick();
	for (System* system : m_systems) {
		system->Update();
	}

	if (GetSystem<InputSystem>()->GetKey(SDL_SCANCODE_ESCAPE)) m_quit = true;

	if (m_scene) m_scene->Update();

	GetSystem<Renderer>()->BeginFrame();
	if (m_scene) m_scene->Draw();
	GetSystem<Renderer>()->EndFrame();
}

bool Engine::LoadScene(const char* scene_name)
{
	m_scene = new Scene();
	m_scene->Create("scene", this);

	rapidjson::Document document;
	json::load(scene_name, document);
	m_scene->Load(document);
	m_scene->Initialize();

	return true;
}

void Engine::DestroyScene()
{
	if (m_scene) {
		m_scene->Destroy();
		delete m_scene;
		m_scene = nullptr;
	}
}
