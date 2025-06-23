#pragma once
#include <SDL.h>

#include "Loging.h"
#include "FactoryOfEntities.h"
#include "Assets.h"
#include "Timer.h"
#include "TextureManager.h"
#include "AudioSystem.h"
#include "InputManager.h"
#include "AnimatedTexture.h"
#include "Weapon.h"
#include "SmoothMoving.h"

class Character : public FactoryOfEntities
{
public:
	Character(SDL_Renderer* pRenderer, const PATH& pPath, const Vector2f& pPos, std::string_view pName, 
			  std::unique_ptr<Weapon> pWeapon = nullptr, const int pLives = 3, const float pSpeed = 5);
	~Character();

	
	void render() override;
	void update() override;

private:
	SDL_Renderer* mRenderer;
	
};

// then for weapons i will make a system of changing. like. 
// weapon - main class, pistol - will be class which i will inherit. 
// then i can pass this into character class