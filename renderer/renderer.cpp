#include "renderer.h"

bool Renderer::Startup()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	return true;
}

void Renderer::Shutdown()
{
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void Renderer::Update()
{
}

void Renderer::CreateWindow(const std::string& name, int width, int height)
{
	m_window = SDL_CreateWindow(name.c_str(), 30, 30, width, height, 0);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

void Renderer::BeginFrame()
{
	SDL_RenderClear(m_renderer);
}

void Renderer::EndFrame()
{
	SDL_RenderPresent(m_renderer);
}
