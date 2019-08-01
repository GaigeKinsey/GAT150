#include "..\\engine\engine.h"
#include "..\\math\vector2.h"
#include "..\\renderer\texture.h"
#include "..\\resources\resource_manager.h"
#include <SDL.h>

int main(int argc, char* args[])
{
	Engine engine;
	engine.Startup();

	Name texture_name("textures/ghost.bmp");
	ResourceManager<Texture> texture_manager(engine.GetRenderer());

	float angle(0.0f);
	vector2 position(30.0f, 30.0f);

	bool quit = false;
	while (!quit) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

		if (keyboardState[SDL_SCANCODE_ESCAPE]) quit = true;
		
		if (keyboardState[SDL_SCANCODE_A]) position.x -= 0.1f;
		if (keyboardState[SDL_SCANCODE_D]) position.x += 0.1f;
		if (keyboardState[SDL_SCANCODE_W]) position.y -= 0.1f;
		if (keyboardState[SDL_SCANCODE_S]) position.y += 0.1f;

		if (keyboardState[SDL_SCANCODE_Q]) angle -= 0.1f;
		if (keyboardState[SDL_SCANCODE_E]) angle += 0.1f;

		engine.Update();

		engine.GetRenderer()->BeginFrame();

		texture_manager.Get(texture_name)->Draw(position, angle, vector2(1.0f, 1.0f), vector2(0.5f, 1.0f));

		engine.GetRenderer()->EndFrame();
	}
	engine.Shutdown();

	return 0;
}
