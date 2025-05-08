#pragma once
#include <filesystem>
#include <string>
#include <unordered_map>
#include <thread>

#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

using PATH = std::filesystem::path;

class TextureManager
{
public:
	static TextureManager& getInstance();

	void appendTexture(SDL_Renderer* pRenderer, const std::string& pName, const PATH& pPath);
	void deleteTexture(const std::string& pName);
	
	SDL_Texture* getTexture(const std::string& pName);
	
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
private:
	TextureManager() = default;
	~TextureManager()
	{
		for (auto& i : mManager)
		{
			SDL_DestroyTexture(i.second);
		}
	}

private:
	inline static TextureManager* msInstance{ nullptr };

	std::unordered_map<std::string, SDL_Texture*> mManager;
	
	PATH mPath{ std::filesystem::current_path() };

	std::mutex mtx;

};

