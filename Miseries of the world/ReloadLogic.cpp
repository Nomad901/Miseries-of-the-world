#include "ReloadLogic.h"

ReloadLogic::ReloadLogic(SDL_Renderer* pRenderer, SDL_Rect pCharRect,
                         float pReloadingTime, bool pShowReloadingQuote)
{
    mTimerReload.setDimensionOfTime(Dimension::MILISECONDS);
  
    mAnimateStateMachine = std::make_unique<AnimateStateMachine>(pRenderer);
    mAnimateStateMachine->pushStateW("ReloadQuote", TypeWait::GENERAL,
                          std::filesystem::current_path() / "Assets" / "photos and ttf" / "reloadQuote.png",
                          { static_cast<float>(pCharRect.x),static_cast<float>(pCharRect.h) }, pCharRect.w+50, pCharRect.h, HorVer::HORIZONTAL,
                          { {SideOfChar::RIGHT, {0,1,2}} }, 10, 300);
    mShowingQuote = pShowReloadingQuote;
    mReloadingTime = pReloadingTime;
}

bool ReloadLogic::isReloading()
{
    return mIsReloading;
}

void ReloadLogic::startReloading()
{
    mIsReloading = true;
}

void ReloadLogic::showReloadQuote(bool pShowing)
{
    mShowingQuote = pShowing;
}

void ReloadLogic::setRelodingTime(float pReloadingTime)
{
    mReloadingTime = pReloadingTime;
}

float ReloadLogic::getReloadingTime()
{
    return mReloadingTime;
}

void ReloadLogic::render(SDL_Renderer* pRenderer)
{
    if (mTimerReload.isRunning())
    {
        if (mShowingQuote)
        {
            if (!mAnimateStateMachine->getState("ReloadQuote").value().get().isActive() ||
                !mAnimateStateMachine->getState("ReloadQuote").value().get().isAnimating())
            {
                mAnimateStateMachine->getState("ReloadQuote").value().get().setCurrentSide(SideOfChar::RIGHT);
                mAnimateStateMachine->getState("ReloadQuote").value().get().setActive(true);
                mAnimateStateMachine->getState("ReloadQuote").value().get().runAnimation();
            }
            mAnimateStateMachine->render("ReloadQuote", false);
        }
    }
    else
    {
        mAnimateStateMachine->getState("ReloadQuote").value().get().setActive(false);
        mAnimateStateMachine->getState("ReloadQuote").value().get().stopAnimation();
    }
}

void ReloadLogic::update(SDL_Rect pCharRect)
{
    if (mIsReloading)
    {
        if (!mTimerReload.isRunning())
            mTimerReload.startTimer();
        if (!manageDelay())
            mIsReloading = false;
        if (mShowingQuote)
        {
            mAnimateStateMachine->getState("ReloadQuote").value().get().setPosition({ static_cast<float>(pCharRect.x),
                                                                                      static_cast<float>(pCharRect.y - pCharRect.h / 2 - 50) });
        }
    }
}

bool ReloadLogic::manageDelay()
{
    if (mTimerReload.isRunning())
    {
        if (mTimerReload.getDeltaTime(false) >= mReloadingTime)
        {
            mTimerReload.stopTimer();
            return false;
        }
        return true;
    }
    return false;
}
