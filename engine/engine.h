#pragma once

#include "..\\renderer\renderer.h"
#include "..\\renderer\texture.h"
#include "..\\audio\audiosystem.h"
#include "..\\input\input_system.h"
#include "..\\resources\resource_manager.h"
#include "..\\framework\event_dispatcher.h"

#include "entity.h"
#include "system.h"

class EntityEventDispatcher : public EventDispatcher<Event<Entity>> {
public:
	EntityEventDispatcher(Engine* engine) : EventDispatcher<Event<Entity>>(engine) {}
};

class Engine
{
public:
	Engine() {}
	~Engine() {}

	bool Startup();
	void Shutdown();
	void Update();

	bool LoadScene(const char* scene_name);
	void DestroyScene();
	Scene* GetScene() { return m_scene; }

	bool Quit() const { return m_quit; }
	
	template <typename T>
	T* GetSystem()
	{
		T* system = nullptr;
		for (System* _system : m_systems)
		{
			system = dynamic_cast<T*>(_system);
			if (system != nullptr) break;
		}

		return system;
	}

	ResourceManager<Resource>* GetResourceManager() { return m_resource_manager; }

private:
	bool m_quit = false;
	class Scene* m_scene = nullptr;

	std::vector<System*> m_systems;

	ResourceManager<Resource>* m_resource_manager = nullptr;
};