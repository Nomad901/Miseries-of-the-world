#include "Handler.h"

Handler::Handler(Game* pGame)
	:mGame(pGame)
{
	mTextures = std::make_unique<Textures>(pGame->getRenderer(), Side::UP);
	mMoving = new Moving(pGame->getRenderer(),mTextures.get());
	
}

Handler::~Handler()
{
	delete mGame;
	delete mMoving;
}

void Handler::loopBack()
{

}

void Handler::actions()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			mGame->stopLoop();
		}
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		mMoving->actions(keystate);

	}
}

void Handler::outro()
{

	mTextures->render();
	
}







