#include "FactoryOfFonts.h"

FactoryOfFonts::FactoryOfFonts(SDL_Renderer* pRenderer)
{
	mRenderer = pRenderer;
	if (TTF_Init() == -1)
		LOG("Couldnt initialize TTF: " + std::string(TTF_GetError()));
}

FactoryOfFonts::FactoryOfFonts(SDL_Renderer* pRenderer, std::string_view pText, const SDL_Color& pColor, const int pSize, const PATH& pPath)
{
	if (TTF_Init() == -1)
		LOG("Couldnt initialize TTF: " + std::string(TTF_GetError()));

	mFont = TTF_OpenFont(pPath.string().c_str(), pSize);
	if (!mFont)
		LOG("Couldnt itialize the path or the font: " + std::string(TTF_GetError()));

	mText = pText;
	mColor = pColor;
	mSize = pSize;

	SDL_Surface* surface = TTF_RenderText_Solid(mFont, mText.c_str(), mColor);
	if (!surface)
		LOG("Couldnt initialize the surface: " + std::string(TTF_GetError()));
	mTexture= SDL_CreateTextureFromSurface(pRenderer, surface);
	if (!mTexture)
		LOG("Problem is texture: " + std::string(SDL_GetError()));
	SDL_FreeSurface(surface);
}

FactoryOfFonts::~FactoryOfFonts()
{
	if (mFont)
		TTF_CloseFont(mFont);
	if (mRenderer)
		SDL_DestroyRenderer(mRenderer);
	if (mTexture)
		SDL_DestroyTexture(mTexture);
	TTF_Quit();
}

void FactoryOfFonts::setNewFont(std::string_view pText, const SDL_Color& pColor, const int pSize, const PATH& pPath)
{
	mFont = TTF_OpenFont(pPath.string().c_str(), pSize);
	if (!mFont)
		LOG("Couldnt itialize the path or the font: " + std::string(TTF_GetError()));

	mText = pText;
	mColor = pColor;
	mSize = pSize;

	SDL_Surface* surface = TTF_RenderText_Solid(mFont, mText.c_str(), mColor);
	if (!surface)
		LOG("Couldnt initialize the surface: " + std::string(TTF_GetError()));
	mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (!mTexture)
		LOG("Problem is texture: " + std::string(SDL_GetError()));
	SDL_FreeSurface(surface);
}

void FactoryOfFonts::changeText(std::string_view pText, const SDL_Color& pColor, const int pSize)
{
	mText = pText;
	mColor = pColor;
	mSize = pSize;

	SDL_Surface* surface = TTF_RenderText_Solid(mFont, mText.c_str(), mColor);
	if (!surface)
		LOG("Couldnt initialize the surface: " + std::string(TTF_GetError()));
	mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (!mTexture)
		LOG("Problem is texture: " + std::string(SDL_GetError()));
	SDL_FreeSurface(surface);
}

void FactoryOfFonts::fontIntoRect(const SDL_Rect pRect)
{	
	int tmpWidth, tmpHeight;
	TTF_SizeText(mFont, mText.c_str(), &tmpWidth, &tmpHeight);
	mRect = { pRect.x + (pRect.w - tmpWidth) / 2, pRect.y + (pRect.h - tmpHeight) / 2, tmpWidth, tmpHeight };
}
