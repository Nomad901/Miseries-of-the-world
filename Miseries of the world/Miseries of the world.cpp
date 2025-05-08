#include <iostream>
#include <filesystem>

#include "Game.h"
#include "Handler.h"

int main(int argc, char* argv[])
{
	static_cast<void>(argc);
	static_cast<void>(argv);
	
	Game* game = new Game (SDL_WINDOW_SHOWN, "Miseries of the world", 100, 100, 1280, 720);
	Handler handler(game);
	game->setRgbOfWindow(0, 150, 150, SDL_ALPHA_OPAQUE);

	game->setFps(60);
	game->setActions(Type::LOOPBACK, [&handler]() {handler.loopBack();});
	game->setActions(Type::ACTIONS,  [&handler]() {handler.actions();});
	game->setActions(Type::OUTRO,    [&handler]() {handler.outro();});
	game->startLoop();


	return 0;
}



/*	
	Today i wanna implement:
	1. adjast bullets(append flyweight design pattern for this)
	2. finish implementing character folder
	3. adjust all of this(like moving properly and also shooting)

	when i will create the character i can create a function which will be observing the character 

	PS at the end i can make a system of inventory, like if inventory is hard my character will be moving slower


*/