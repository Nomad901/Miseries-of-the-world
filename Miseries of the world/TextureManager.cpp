#include "TextureManager.h"


TextureManager& TextureManager::getInstance()
{
	if (msInstance == nullptr)
		msInstance = new TextureManager();
	return *msInstance;
}

void TextureManager::appendTexture(SDL_Renderer* pRenderer, const std::string& pName, const PATH& pPath)
{
	std::lock_guard<std::mutex> lc(mtx);

	SDL_Surface* surface = IMG_Load(pPath.string().c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
	mManager.insert_or_assign(pName, texture);
	SDL_FreeSurface(surface);
}

void TextureManager::deleteTexture(const std::string& pName)
{
	std::lock_guard<std::mutex> lc(mtx);

	if (mManager.find(pName) == mManager.end())
	{
		LOG("There is not such a texture!");
		return;
	}
	SDL_DestroyTexture(mManager[pName]);
}

SDL_Texture* TextureManager::getTexture(const std::string& pName)
{
	std::lock_guard<std::mutex> lc(mtx);

	auto it = mManager.find(pName);
	return (it == mManager.end()) ? nullptr : it->second;
}
