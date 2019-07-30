#include "..\\math\vector2.h"
#include <SDL.h>
#include <iostream>

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("game", 30, 30, 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* surface = SDL_LoadBMP("textures/ghost.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

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
				}
			}
		}

		SDL_RenderClear(renderer);

		SDL_Rect dest = { position.x, position.y, 32, 32 };
		SDL_QueryTexture(texture, 0, 0, &dest.w, &dest.h);

		//SDL_RenderCopy(renderer, texture, NULL, &dest);
		SDL_RenderCopyEx(renderer, texture, NULL, &dest, angle, 0, SDL_FLIP_NONE);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
