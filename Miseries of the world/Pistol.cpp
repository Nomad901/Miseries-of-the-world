#include "Pistol.h"
//#include "Pistol.h"
//#include "Timer.h"
//#include "BulletsPool.h"
//
//Pistol::Pistol(SDL_Renderer* pRenderer,
//			   const Vector2f& pPos, int pW, int pH, std::pair<int32_t, int32_t> pPower, 
//			   int32_t pQuantityBullets, int32_t pQuantityOfSets, int32_t pReloadingTime, 
//			   const PATH& pStaticPath, const PATH& pBrokenWeaponPath, const PATH& pReloadingPath, const PATH& pShootingPath, 
//			   SDL_Rect pChar)
//	: mRenderer{ pRenderer }
//{
//	Weapon::takeWeapon(pChar);
//	Weapon::setMousePos(pPos);
//	Weapon::setAllParameteres(pPos, pW, pH, pQuantityBullets, pQuantityOfSets, 100, pPower, pReloadingTime, 20);
//	Weapon::setAllPaths(pStaticPath, pBrokenWeaponPath, pReloadingPath, pShootingPath);
//
//	FactoryOfFonts::getInstance().appendNewFont(pRenderer,
//		std::filesystem::current_path() / "Assets" / "photos and ttf" / "Arial.ttf",
//		std::to_string(pReloadingTime), { 255,255,255,255 }, 24);
//
//	SDL_Rect tmpRect = { static_cast<int32_t>(pPos.mX), static_cast<int32_t>(pPos.mY), pW, pH };
//	TextureManager::getInstance().appendTexture(pRenderer, pStaticPath, tmpRect);
//	TextureManager::getInstance().appendTexture(pRenderer, pBrokenWeaponPath, tmpRect);
//
//	mReloadTexture.appendAnimation(TypeWait::GENERAL, pRenderer, pReloadingPath, pPos, pW - 20, pH - 5, HorVer::HORIZONTAL);
//	mShootingTexture.appendAnimation(TypeWait::GENERAL, pRenderer, pShootingPath, pPos, pW - 20, pH - 5, HorVer::HORIZONTAL);
//
//	mFactoryObjects.appendRect("Timer", { static_cast<int32_t>(Weapon::getPos().mX) + 20, static_cast<int32_t>(Weapon::getPos().mX) - 20, 50,50 }, { 255,255,255,255 });
//
//	mTimer.setDimensionOfTime(Dimension::SECONDS);
//	mTimerOfSets.setDimensionOfTime(Dimension::MILISECONDS);
//
//	mBullets = std::make_unique<BulletsPool>();
//	mBullets->init(500, mRenderer, std::filesystem::current_path() / "Assets" / "photos and ttf" / "bulletV2.png", pPos, 50, 50, 10);
//}
//
//void Pistol::adjustReloadAnim(const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, float pIntensity)
//{
//	mReloadTexture.setSides(pNumbers);
//	mReloadTexture.setIntensity(pIntensity);
//}
//
//void Pistol::adjustShootAnim(const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, float pIntensity)
//{
//	mShootingTexture.setSides(pNumbers);
//	mShootingTexture.setIntensity(pIntensity);
//}
//
//bool Pistol::WeaponIsInView(SDL_Rect pCharCollision)
//{
//	if (mObjects.areColliding(pCharCollision, TextureManager::getInstance().getRect(Weapon::getStaticPath())))
//		return true;
//	else
//		return false;
//}
//
//void Pistol::shoot()
//{
//	//std::cout << std::format("Quantity of Bullets: {}\n", Weapon::getQuantityBullets());
//	if (Weapon::getRobustness() > 0 && !Weapon::isFreezed())
//	{
//		static int32_t tmpOrigSourceBullets = Weapon::getOrigQuantityBullets() - 6;
//		if (Weapon::neededToReload())
//		{
//			if (!mTimer.isRunning())
//				mTimer.startTimer();
//			tmpOrigSourceBullets = Weapon::getOrigQuantityBullets();
//		}
//		else
//		{
//			if (!mTimer.isRunning() && Weapon::getQuantityOfSets() != 0)
//			{
//				if (manageDelay())
//					return;
//
//				if (!mShootingTexture.isActive())
//				{
//					mShootingTexture.setCurrentSide(SideOfChar::RIGHT);
//					mShootingTexture.setActive(true);
//					mShootingTexture.runAnimation();
//				}
//
//				mRotateMachine.calculateRadians(Weapon::getWeaponStats().mPos, InputManager::getInstance().getMousePos());
//
//				mBullets->makeBulletActive();
//				mBullets->manageLastBulletInside()->setSpeed(10);
//				auto tmpPos = Weapon::getWeaponStats().mPos;
//				mBullets->manageLastBulletInside()->shootBullet({ tmpPos.mX + Weapon::getWeaponStats().mW - 40, tmpPos.mY }, InputManager::getInstance().getMousePos(),
//																  mRotateMachine.getAngle(), TextureManager::getInstance().getRect(Weapon::getStaticPath()),
//																{ static_cast<float>(TextureManager::getInstance().getRect(Weapon::getStaticPath()).w / 2 - 10),-5 },
//																  Weapon::getCharCollision().w, Weapon::getCharCollision().h);
//
//				if (tmpOrigSourceBullets > Weapon::getQuantityBullets())
//				{
//					mForRobustness.generateNew();
//					Weapon::setRobustness(static_cast<float>(Weapon::getRobustness() - mForRobustness.getNumber()));
//					tmpOrigSourceBullets -= 6;
//				}
//				Weapon::setQuantityOfBullets(Weapon::getQuantityBullets() - 1);
//				//std::cout << std::format("Quantity of bullets: {}\n", Weapon::getQuantityBullets());
//			}
//		}
//	}
//}
//
//void Pistol::reload()
//{
//	if (Weapon::getRobustness() > 0 && !Weapon::isFreezed())
//	{
//		if (!mReloadTexture.isActive())
//		{
//			mShootingTexture.setActive(false);
//
//			mReloadTexture.setCurrentSide(SideOfChar::RIGHT);
//			mReloadTexture.setActive(true);
//			mReloadTexture.runAnimationOnlyOnce();
//		}
//		if (!mTimer.isRunning())
//			mTimer.startTimer();
//
//		static int32_t prevTimeOfTimer = mTimer.getDeltaTime(false);
//		if (mTimer.getDeltaTime(false) > prevTimeOfTimer)
//		{
//			mReloadCounter++;
//			FactoryOfFonts::getInstance().changeText(mRenderer,
//				std::to_string(Weapon::getReloadingTime()), std::to_string(Weapon::getReloadingTime() - mReloadCounter),
//				{ 255,255,255,255 });
//			prevTimeOfTimer = mTimer.getDeltaTime(false);
//		}
//		if (mTimer.getDeltaTime(false) == Weapon::getReloadingTime())
//		{
//			Weapon::setQuantityOfBullets(Weapon::getOrigQuantityBullets());
//			Weapon::setQuantityOfSets(Weapon::getQuantityOfSets() - 1);
//			prevTimeOfTimer = 0;
//			mReloadCounter = 0;
//			mReloadTexture.setActive(false);
//			mReloadTexture.nullTicks();
//			mTimer.stopTimer();
//		}
//	}
//}
//
//void Pistol::render(SDL_Renderer* pRenderer)
//{
//	if (!Weapon::isFreezed())
//	{
//		if (mTimer.isRunning())
//		{
//			mFactoryObjects.render("Timer", pRenderer, false);
//			FactoryOfFonts::getInstance().render(std::to_string(Weapon::getReloadingTime() - mReloadCounter), pRenderer, mFactoryObjects.getRect("Timer"));
//
//			if (mReloadTexture.isActive() && !mShootingTexture.isActive())
//				mReloadTexture.renderWithRotate(pRenderer, mRotateMachine.getAngle() * 180 / M_PI, Weapon::getWeaponStats().mPosMouse);
//		}
//		if (!mReloadTexture.isActive())
//		{
//			if (mShootingTexture.isActive() && !mReloadTexture.isActive())
//			{
//				if (!mTimerForShooting.isRunning())
//				{
//					mTimerForShooting.setDimensionOfTime(Dimension::MILISECONDS);
//					mTimerForShooting.startTimer();
//				}
//				mShootingTexture.renderWithRotate(pRenderer, mRotateMachine.getAngle() * 180 / M_PI, Weapon::getWeaponStats().mPosMouse);
//				if (mTimerForShooting.getDeltaTime(false) >= 600)
//				{
//					mShootingTexture.setActive(false);
//					mTimerForShooting.stopTimer();
//				}
//			}
//			else
//				brokenChecker(pRenderer);
//		}
//	}
//	else
//	{
//		brokenChecker(pRenderer);
//	}
//	mBullets->update();
//}
//
//void Pistol::update()
//{
//	if (mTimer.isRunning())
//	{
//		mFactoryObjects.setPosition("Timer", { static_cast<float>(Weapon::getPos().mX + 50),static_cast<float>(Weapon::getPos().mY - 50) });
//		if (mReloadTexture.isActive())
//			mReloadTexture.setPosition(Weapon::getWeaponStats().mPos);
//		reload();
//	}
//	if (!Weapon::isFreezed())
//	{
//		TextureManager::getInstance().setPosition(Weapon::getStaticPath(), Weapon::getPos());
//		TextureManager::getInstance().setPosition(Weapon::getBrokenPath(), Weapon::getPos());
//	}
//
//	mShootingTexture.setPosition(Weapon::getWeaponStats().mPos);
//}
//	
//void Pistol::setAsADefaultWeapon()
//{
//	Weapon::defaultParametersWeapons();
//}
//
//void Pistol::setAsASpecialWeapon()
//{
//	defaultParametersPistol();
//}
//
//bool Pistol::checkRobustness()
//{
//	if (Weapon::getWeaponStats().mScaleOfRobustness == 0)
//		return true;
//	return false;
//}
//
//
//void Pistol::manageRotate()
//{
//	mRotateMachine.calculateRadians(Weapon::getWeaponStats().mPos, Weapon::getWeaponStats().mPosMouse);
//}
//
//bool Pistol::manageDelay()
//{
//	if (!mTimerOfSets.isRunning())
//		mTimerOfSets.startTimer();
//	if (mTimerOfSets.getDeltaTime(false) <= Weapon::getWeaponStats().mDelay)
//		return true;
//	else
//		mTimerOfSets.stopTimer();
//	return false;
//}
//
//void Pistol::defaultParametersPistol()
//{
//	std::string origReloadTime = std::to_string(Weapon::getOrigReloadTime());
//
//	Weapon::setRobustness(100);
//	Weapon::setTimeOfDelay(500);
//	Weapon::setQuantityOfBullets(15);
//	Weapon::setOrigQuantityBullets(15);
//	Weapon::setQuantityOfSets(15);
//	Weapon::setReloadingTime(2);
//	Weapon::setOrigReloadTime(3);
//	Weapon::setWeight(5);
//	Weapon::setPower(std::make_pair(3, 6));
//
//	FactoryOfFonts::getInstance().changeText(mRenderer, origReloadTime, std::to_string(Weapon::getReloadingTime()), { 255,255,255,255 });
//}
//
//void Pistol::brokenChecker(SDL_Renderer* pRenderer)
//{
//	if (!Weapon::isFreezed())
//	{
//		if (Weapon::getRobustness() > 0)
//			SDL_RenderCopyEx(pRenderer, TextureManager::getInstance().getTexture(Weapon::getStaticPath()), nullptr,
//							 &TextureManager::getInstance().getRect(Weapon::getStaticPath()), mRotateMachine.getAngle() * 180 / M_PI, nullptr,
//							 Weapon::getWeaponStats().mPosMouse.mX >= Weapon::getWeaponStats().mPos.mX ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
//		else
//			SDL_RenderCopyEx(pRenderer, TextureManager::getInstance().getTexture(Weapon::getBrokenPath()), nullptr,
//							 &TextureManager::getInstance().getRect(Weapon::getBrokenPath()), mRotateMachine.getAngle() * 180 / M_PI, nullptr,
//							 Weapon::getWeaponStats().mPosMouse.mX >= Weapon::getWeaponStats().mPos.mX ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
//	}
//	else
//	{
//		if (Weapon::getRobustness() > 0)
//			SDL_RenderCopy(pRenderer, TextureManager::getInstance().getTexture(Weapon::getStaticPath()), nullptr,
//						   &TextureManager::getInstance().getRect(Weapon::getStaticPath()));
//		else
//			SDL_RenderCopy(pRenderer, TextureManager::getInstance().getTexture(Weapon::getBrokenPath()), nullptr,
//						   &TextureManager::getInstance().getRect(Weapon::getBrokenPath()));
//	}
//}

void Pistol::shoot()
{
}

void Pistol::checkRobustness()
{
}

void Pistol::checkDamage()
{
}

void Pistol::setAsASpecialWeapon()
{
}

bool Pistol::manageDelay()
{
	return false;
}
