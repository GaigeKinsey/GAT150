#include "..\\engine\engine.h"

int main(int argc, char* args[])
{
	Engine engine;
	engine.Startup();

	while (!engine.Quit()) {
		engine.Update();
	}

	engine.Shutdown();

	return 0;
}
