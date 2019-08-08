#include "engine.h"
#include "scene.h"
#include "entity.h"
#include "..\\core\filesystem.h"
#include "..\\core\name.h"

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

	m_texture_manager = new ResourceManager<Texture>(renderer);

	m_scene = new Scene();
	m_scene->Create("scene", this);

	rapidjson::Document document;
	json::load("scenes/scene.txt", document);
	m_scene->Load(document);

	Entity* entity = m_scene->GetComponentFactory()->Create<Entity>("asteroid");
	m_scene->Add(entity);

	return true;
}

void Engine::Shutdown()
{
	for (System* system : m_systems) {
		system->Shutdown();
		delete system;
	}
	m_systems.clear();

	m_texture_manager->RemoveAll();
	delete m_texture_manager;

	m_scene->Destroy();
	delete m_scene;

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
