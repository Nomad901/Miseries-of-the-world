#include "Bullets.h"

Bullets::Bullets(SDL_Renderer* pRenderer,
				 const PATH& pPath, const Vector2f& pPos,
				 int32_t pW, int32_t pH, int32_t pSpeed)
	: mPos{ pPos }, mRenderer(pRenderer), 
	  mSpeed{pSpeed}, mPath{pPath}
{
	mRect = { static_cast<int>(pPos.mX),static_cast<int>(pPos.mY), pW ,pH };
	TextureManager::getInstance().appendTextureWithoutBack(pRenderer, pPath, mRect, { 34,177,76,255 });
}

void Bullets::shootBullet(const Vector2f& pPlayerPos, const Vector2f& pMousePos, SDL_Rect pWeaponRect,
						  double pAngle, const Vector2f& pOffset, int32_t pW, int32_t pH)
{
	Vector2f centerPos = { pPlayerPos.mX + pW / 2.0f, pPlayerPos.mY + pH / 2.0f };
	mPos = centerPos;
	mAttachedOffset = pOffset;

	mRotateMachine.calculateDirection(pPlayerPos, pMousePos, pW, pH);
	mRotateMachine.calculateLength(mRotateMachine.getDirection());

	if (mRotateMachine.getLength() > 0.1f) {
		mRotateMachine.calculateSpeed(mRotateMachine.getDirection(),
									  mRotateMachine.getLength(),
									  mSpeed);

		mRotateMachine.setAngle(pAngle);

		mActive = true;
		updateAttachedRect(pWeaponRect);
	}
}

bool Bullets::isColliding(SDL_Rect pRect)
{
	pRect.w -= 32;
	pRect.h -= 30;
	pRect.x += 20;
	pRect.y += 20;

	return SDL_HasIntersection(&mRect, &pRect);
}

bool Bullets::isActive()
{
	return mActive;
}

bool Bullets::checkBoundaries()
{
	if (mPos.mX >= WIN_WIDTH + mRect.w  || mPos.mX <= -50 ||
		mPos.mY >= WIN_HEIGHT + 100		|| mPos.mY <= -50)
		return true;
	return false;
}

SDL_Rect& Bullets::getShape()
{
	return TextureManager::getInstance().getRect(mPath);
}

Vector2f Bullets::getPos() const noexcept
{
	return { static_cast<float>(mRect.x), static_cast<float>(mRect.y) };
}

void Bullets::setPos(const Vector2f& pPos)
{
	mPos = pPos;
	mRect.x = static_cast<int>(pPos.mX);
	mRect.y = static_cast<int>(pPos.mY);
}

int32_t Bullets::getSpeed() const noexcept
{
	return mSpeed;
}

void Bullets::setSpeed(int32_t pSpeed)
{
	mSpeed = pSpeed;
}

PATH Bullets::getPath()
{
	return mPath;
}

void Bullets::setPath(const PATH& pPath)
{
	mPath = pPath;
	if (TextureManager::getInstance().containsPath(pPath))
		TextureManager::getInstance().appendTextureWithoutBack(mRenderer, pPath, mRect, { 34,177,76,255 });
}

void Bullets::render()
{
	if (mActive)
	{
		if(!TextureManager::getInstance().containsPath(mPath))
			TextureManager::getInstance().appendTextureWithoutBack(mRenderer, mPath, mRect, { 34,177,76,255 });
		SDL_RenderCopyEx(mRenderer, TextureManager::getInstance().getTexture(mPath), nullptr, &mRect, mRotateMachine.getAngle(), nullptr,
						 mMousePos.mX >= mPos.mX ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
	}
}

void Bullets::update()
{
	if (mActive)
	{
		if (checkBoundaries())
			mActive = false;
		mRect.x += static_cast<int>(mRotateMachine.getSpeed().mX);
		mRect.y += static_cast<int>(mRotateMachine.getSpeed().mY);

		mPos.mX = static_cast<float>(mRect.x);
		mPos.mY = static_cast<float>(mRect.y);
	}
}

void Bullets::updateAttachedRect(SDL_Rect pWeaponRect)
{
	float angleRect = mRotateMachine.getAngle() * M_PI / 180;
	
	float rotatedX = mAttachedOffset.mX * cos(angleRect) - mAttachedOffset.mY * sin(angleRect);
	float rotatedY = mAttachedOffset.mX * sin(angleRect) + mAttachedOffset.mY * cos(angleRect);

	mRect.x = pWeaponRect.x + pWeaponRect.w / 2 + static_cast<int>(rotatedX) - mRect.w / 2;
	mRect.y = pWeaponRect.y + pWeaponRect.h / 2 + static_cast<int>(rotatedY) - mRect.h / 2;	
}

