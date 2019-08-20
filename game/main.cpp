#include "game.h"

int main(int argc, char* args[])
{
	Engine* engine = new Engine();
	Game game(engine);

	game.Startup();

	while (!game.Quit()) {
		game.Update();
	}

	game.Shutdown();

	return 0;
}
