// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <filesystem>

#include "Game.h"
#include "Handler.h"

int main(int argc, char* argv[])
{
	static_cast<void>(argc);
	static_cast<void>(argv);
	
	std::unique_ptr<Game> game = std::make_unique<Game>(SDL_WINDOW_SHOWN, "Miseries of the world", 100, 100);
	Handler handler(game.get());
	game->setRgbOfWindow(0, 150, 150, SDL_ALPHA_OPAQUE);

	game->setFps(144);
	game->setActions(Type::LOOPBACK, [&handler]() {handler.loopBack();});
	game->setActions(Type::ACTIONS,  [&handler]() {handler.actions();});
	game->setActions(Type::OUTRO,    [&handler]() {handler.outro();});
	game->startLoop();


	return 0;
}



/*	
	TODO: correct bugs in Tango




	when i will create the character i can create a function which will be observing the character 

	PS at the end i can make a system of inventory, like if inventory is hard my character will be moving slower



	// This is a personal academic project. Dear PVS-Studio, please check it.

	// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


*/