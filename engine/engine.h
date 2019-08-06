#pragma once

#include "..\\renderer\renderer.h"
#include "..\\renderer\texture.h"
#include "..\\audio\audiosystem.h"
#include "..\\resources\resource_manager.h"

#include "system.h"

class Engine
{
public:
	Engine() {}
	~Engine() {}

	bool Startup();
	void Shutdown();
	void Update();

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

	ResourceManager<Texture>* GetTextureManager() { return m_texture_manager; }

private:
	bool m_quit = false;
	class Scene* m_scene = nullptr;

	std::vector<System*> m_systems;

	ResourceManager<Texture>* m_texture_manager = nullptr;
};