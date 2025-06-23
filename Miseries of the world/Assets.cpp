#include "Assets.h"
#include "TextureManager.h"
#include "../FactoryOfFonts.h"

void Assets::download()
{

}

auto Assets::getAnimation(const PATH& pPath) -> std::unordered_map<int, std::pair<SDL_Texture*, SDL_Rect>>
{
    if (mAnimation.find(pPath) == mAnimation.end())
    {
        LOG("couldnt find the path!");
        return { {0,{nullptr,{0,0,0,0}}} };
    }
    mAssets[0].writeIntoFile(pPath.string(), "anim");
    return mAnimation[pPath];
}

SDL_Texture* Assets::getTexture(const PATH& pPath)
{
    if (mTextures.find(pPath) == mTextures.end())
    {
        TextureManager::getInstance().appendTexture(mRenderer, pPath, { 100,100,100,100 });
        mAssets[1].writeIntoFile(pPath.string(), "textures");
    }

    return mTextures[pPath].first.second;
}

SDL_Surface* Assets::getSurface(const PATH& pPath)
{
    if (mTextures.find(pPath) == mTextures.end())
    {
        TextureManager::init();
        TextureManager::getInstance().appendTexture(mRenderer, pPath, { 100,100,100,100 });
        mAssets[2].writeIntoFile(pPath.string(), "surface");
        TextureManager::shutDown();
    }

    return mTextures[pPath].first.first;
}

TTF_Font* Assets::getFonts(std::string_view pAlias)
{
    if (mFonts.find(std::string(pAlias)) != mFonts.end())
    {
        mAssets[3].writeIntoFile(std::string(pAlias), "font");
        return mFonts[std::string(pAlias)].first;
        //if (!mFonts[std::string(pAlias)].first)
        //    LOG("Couldnt itialize the path or the font: " + std::string(TTF_GetError()));
    }
    return nullptr;
}

SDL_Texture* Assets::getTextureFont(std::string_view pAlias)
{
    if (mFonts.find(std::string(pAlias)) != mFonts.end())
    {
        mAssets[3].writeIntoFile(std::string(pAlias), "font");
        return mFonts[std::string(pAlias)].second;
    }
    return nullptr;
}

Mix_Chunk* Assets::getSound(const PATH& pPath)
{
    if (mSounds.find(pPath) == mSounds.end())
    {
        mSounds.insert_or_assign(pPath, Mix_LoadWAV(pPath.string().c_str()));
        if(!mSounds[pPath])
            LOG("Couldnt itialize the path or the sound: " + std::string(Mix_GetError()));
        mAssets[4].writeIntoFile(pPath.string(), "sounds");
    }
    return mSounds[pPath];
}

Mix_Music* Assets::getMusic(const PATH& pPath)
{
    if (mMusic.find(pPath) == mMusic.end())
    {
        mMusic.insert_or_assign(pPath,Mix_LoadMUS(pPath.string().c_str()));
        if(!mMusic[pPath])
            LOG("Couldnt itialize the path or the music: " + std::string(Mix_GetError()));
        mAssets[5].writeIntoFile(pPath.string(), "music");
    }
    return mMusic[pPath];
}

PATH Assets::getScene(std::string_view pScene)
{
    if (!mScenes.contains(std::string(pScene)))
    {
        LOG("there is no such a scene!");
        return "";
    }
    return mScenes[std::string(pScene)];
}

Assets::~Assets()
{
    for (auto& i : mMusic)
    {
        Mix_FreeMusic(i.second);
    }
    mMusic.clear();
    for (auto& i : mSounds)
    {
        Mix_FreeChunk(i.second);
    }
    mSounds.clear();
    for (auto& i : mTextures)
    {
        SDL_FreeSurface(i.second.first.first);
        SDL_DestroyTexture(i.second.first.second);
    }
    mTextures.clear();
    for (auto& i : mFonts)
    {
        TTF_CloseFont(i.second.first);
        SDL_DestroyTexture(i.second.second);
    }
    mFonts.clear();

    SDL_DestroyRenderer(mRenderer);
}
