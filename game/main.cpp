#include "..\\engine\engine.h"
#include "..\\math\vector2.h"
#include "..\\renderer\texture.h"
#include <SDL.h>

int main(int argc, char* args[])
{
	Engine engine;
	engine.Startup();

	Texture texture(engine.GetRenderer());
	texture.Create("textures/ghost.bmp");

	float angle(0.0f);
	vector2 position(30.0f, 30.0f);

	bool quit = false;
	while (!quit) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					position.x -= 1.0f;
					break;
				case SDLK_RIGHT:
					position.x += 1.0f;
					break;
				case SDLK_UP:
					angle += 1.0f;
					break;
				case SDLK_DOWN:
					angle -= 1.0f;
					break;
				default:
					break;
				}
			}
		}
		engine.Update();

		engine.GetRenderer()->BeginFrame();

		texture.Draw(position, vector2(0, 0), vector2::one, angle);

		engine.GetRenderer()->EndFrame();
	}
	engine.Shutdown();

	return 0;
}
