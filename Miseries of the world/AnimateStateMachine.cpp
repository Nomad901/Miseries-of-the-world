#include "AnimateStateMachine.h"

AnimateStateMachine::AnimateStateMachine(SDL_Renderer* pRenderer, std::string_view pName, std::unique_ptr<AnimatedTexture> pAnimatedTexture,
										 const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, int32_t pDelay, float pItensity)
	: mState{ std::string(pName) }, mRenderer{ pRenderer }
{
	mNames.reserve(50);
	mNames.push_back(std::string(pName));
	if (!mStorageTextures.contains(mState))
		mStorageTextures[mState].mAnimatedTexture = std::move(pAnimatedTexture);
	mStorageTextures[mState].mAnimatedTexture->setSides(pNumbers);
	mStorageTextures[mState].mDelay = pDelay;
	mStorageTextures[mState].mAnimatedTexture->setIntensity(pItensity);
}

AnimateStateMachine::AnimateStateMachine(SDL_Renderer* pRenderer, std::string_view pName, TypeWait pType, const PATH& pPath,
										 const Vector2f& pPos, const int pW, const int pH, HorVer pSide, 
										 const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, int32_t pDelay, float pItensity)
	: mState{ std::string(pName) }, mRenderer{ pRenderer }
{
	mNames.reserve(50);
	mNames.push_back(std::string(pName));
	std::unique_ptr<AnimatedTexture> tmpAnimated = std::make_unique<AnimatedTexture>();
	tmpAnimated->appendAnimation(pType, pRenderer, pPath, pPos, pW, pH, pSide);
	tmpAnimated->setSides(pNumbers);
	mStorageTextures[mState].mAnimatedTexture = std::move(tmpAnimated);
	mStorageTextures[mState].mDelay = pDelay;
	mStorageTextures[mState].mAnimatedTexture->setIntensity(pItensity);
}

void AnimateStateMachine::pushState(std::string_view pName, std::unique_ptr<AnimatedTexture> pState,
								    const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, int32_t pDelay, float pItensity)
{
	mState = std::string(pName);
	mNames.push_back(std::string(pName));
	if (!mStorageTextures.contains(mState))
		mStorageTextures[mState].mAnimatedTexture = std::move(pState);
	mStorageTextures[mState].mAnimatedTexture->setSides(pNumbers);
	mStorageTextures[mState].mDelay = pDelay;
	mStorageTextures[mState].mAnimatedTexture->setIntensity(pItensity);
}

void AnimateStateMachine::pushState(std::string_view pName, TypeWait pType, const PATH& pPath, 
									const Vector2f& pPos, const int pW, const int pH, HorVer pSide,
									const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, int32_t pDelay, float pItensity)
{
	mState = std::string(pName);
	mNames.push_back(std::string(pName));
	std::unique_ptr<AnimatedTexture> tmpAnimated = std::make_unique<AnimatedTexture>();
	tmpAnimated->appendAnimation(pType, mRenderer, pPath, pPos, pW, pH, pSide);
	tmpAnimated->setSides(pNumbers);
	mStorageTextures[mState].mAnimatedTexture = std::move(tmpAnimated);
	mStorageTextures[mState].mDelay = pDelay;
	mStorageTextures[mState].mAnimatedTexture->setIntensity(pItensity);
}

void AnimateStateMachine::popState(std::string_view pName)
{
	if (mState == pName)
		mState.clear();
	if (mStorageTextures.contains(std::string(pName)))
	{
		mStorageTextures[std::string(pName)].mAnimatedTexture.release();
		mStorageTextures[std::string(pName)].mAnimatedTexture = nullptr;
		mStorageTextures.erase(std::string(pName));

		if (std::ranges::contains(mNames, std::string(pName)))
		{
			auto it = std::remove(mNames.begin(), mNames.end(), std::string(pName));
			mNames.erase(it);
		} 
	}
	else
		LOG("There is no such a name!");
}

bool AnimateStateMachine::findState(std::string_view pName) const
{
	if (mStorageTextures.contains(std::string(pName)))
		return true;
	LOG("There is no such a name!");
	return false;
}

void AnimateStateMachine::setCurrentState(std::string_view pName)
{
	if (mStorageTextures.contains(std::string(pName)))
		mState = std::string(pName);
	else
		LOG("There is no such a name!");
}

void AnimateStateMachine::adjustState(std::string_view pName, const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, 
									  int32_t pDelay, float pItensity)
{
	if (mStorageTextures.contains(std::string(pName)))
	{
		mState = std::string(pName);
		if (mStorageTextures[mState].mAnimatedTexture != nullptr)
		{
			mStorageTextures[mState].mDelay = pDelay;
			mStorageTextures[mState].mAnimatedTexture->setSides(pNumbers);
			mStorageTextures[mState].mAnimatedTexture->setIntensity(pItensity);
		}
		else
			LOG("Storage with this name is empty!");
	}
	else
		LOG("There is no such a name!");
}

void AnimateStateMachine::setDelay(int32_t pDelay)
{
	mStorageTextures[mState].mDelay = pDelay;
}

void AnimateStateMachine::setDelay(std::string_view pName, int32_t pDelay)
{
	mState = std::string(pName);
	mStorageTextures[mState].mDelay = pDelay;
}

int32_t AnimateStateMachine::getDelay()
{
	return mStorageTextures[mState].mDelay;
}

int32_t AnimateStateMachine::getDelay(std::string_view pName)
{
	if (mStorageTextures.contains(std::string(pName)))
		return mStorageTextures[std::string(pName)].mDelay;
	return 0;
}

void AnimateStateMachine::renderAndUpdate(bool pRotate, float pAngle)
{
	if (!mStorageTextures[mState].mAnimatedTexture->isEnded())
	{
		if (pRotate)
			mStorageTextures[mState].mAnimatedTexture->renderWithRotate(mRenderer, pAngle, InputManager::getInstance().getMousePos());
		else
			mStorageTextures[mState].mAnimatedTexture->render(mRenderer);
	}
	else
	{
		if (!mTimer.isRunning())
			mTimer.startTimer();
		if (mTimer.getDeltaTime(false) >= mStorageTextures[mState].mDelay)
		{
			mStorageTextures[mState].mAnimatedTexture->setEnded(false);
			mTimer.stopTimer();
		}
	}
}

void AnimateStateMachine::render(std::string_view pName, bool pRotate, float pAngle)
{
	if (mState == std::string(pName))
		renderAndUpdate(pRotate, pAngle);
	else
	{
		if (mStorageTextures.contains(std::string(pName)))
		{
			mState = std::string(pName);
			renderAndUpdate(pRotate, pAngle);
		}
		else
			LOG("There is no such a name!");
	}
}

void AnimateStateMachine::render(const std::vector<std::string>& pNames, bool pRotate, float pAngle)
{
	if (std::ranges::equal(mNames, pNames))
	{
		for (const auto& name : mNames)
			render(name, pRotate, pAngle);
	}
	else
	{
		mNames.clear();
		for (const auto& name : pNames)
		{
			if (mStorageTextures.contains(name))
			{
				render(name, pRotate, pAngle);
				mNames = pNames;
			}
			else
			{
				LOG("There is no such names!");
				break;
			}
		}
	}
}

std::unique_ptr<AnimatedTexture>& AnimateStateMachine::getState(std::string_view pName)
{
	if (mState == std::string(pName))
		getState();
	else {
		if (mStorageTextures.contains(std::string(pName)))
		{
			mState = std::string(pName);
			return mStorageTextures[mState].mAnimatedTexture;
		}
		else
			LOG("There is no such a name!");
	}
}

std::unique_ptr<AnimatedTexture>& AnimateStateMachine::getState() 
{
	return mStorageTextures[mState].mAnimatedTexture;
}
