#pragma once

#include "..\\engine\system.h"
#include "..\\external\SDL2-2.0.10\include\SDL.h"
#include "..\\external\SDL2-2.0.10\include\SDL_image.h"
#include <string>

class Renderer : public System
{
public:
	Renderer(Engine* engine) : System(engine) {}
	~Renderer() {}
	
	bool Startup();
	void Shutdown();
	void Update();

	void CreateWindow(const std::string& name, int width, int height);
	void BeginFrame();
	void EndFrame();

	SDL_Renderer* GetSDLRenderer() { return m_renderer; }

private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};