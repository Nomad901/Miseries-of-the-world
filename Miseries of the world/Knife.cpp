//#include "Knife.h"
//#include "Timer.h"
//
//
//Knife::Knife(SDL_Renderer* pRenderer,
//			 const Vector2f& pPos, int pW, int pH, std::pair<int32_t, int32_t> pPower, int16_t pDelay,
//			 const PATH& pStaticPath, const PATH& pBrokenPath, const PATH& pShootingPath,
//			 SDL_Rect pChar, SDL_Rect pHitBoxOfAttack)
//	: mRenderer{ pRenderer }, mHitBoxKnife{ pHitBoxOfAttack }
//{
//	Weapon::takeWeapon(pChar);
//	Weapon::setMousePos(pPos);
//	Weapon::setAllParameteres(pPos, pW, pH, 0, 0, 100, pPower, 0, 20);
//	Weapon::setTimeOfDelay(pDelay);
//	Weapon::setAllPaths(pStaticPath, pBrokenPath, std::filesystem::current_path(), pShootingPath);
//
//	SDL_Rect tmpRect = { static_cast<int32_t>(pPos.mX), static_cast<int32_t>(pPos.mY), pW, pH };
//	TextureManager::getInstance().appendTexture(pRenderer, pStaticPath, tmpRect);
//	TextureManager::getInstance().appendTexture(pRenderer, pBrokenPath, tmpRect);
//
//	mShootingTexture.appendAnimation(TypeWait::GENERAL, pRenderer, pShootingPath, pPos, pW - 20, pH - 5, HorVer::HORIZONTAL);
//
//	mDelayTimer.setDimensionOfTime(Dimension::MILISECONDS);
//}
//
//int16_t Knife::getDelay() const noexcept
//{
//	return mDelay;
//}
//
//void Knife::setDelay(int16_t pDelay)
//{
//	mDelay = pDelay;
//}
//
//SDL_Rect Knife::getHitBoxOfAttack()
//{
//	return mHitBoxKnife;
//}
//
//void Knife::setHitBoxOfAttack(SDL_Rect pRect)
//{
//	mHitBoxKnife = pRect;
//}
//
//void Knife::adjustShootAnim(const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, float pIntensity)
//{
//	mShootingTexture.setSides(pNumbers);
//	mShootingTexture.setIntensity(pIntensity);
//}
//
//bool Knife::WeaponIsInView(SDL_Rect pCharCollision)
//{
//	if (mObjects.areColliding(pCharCollision, TextureManager::getInstance().getRect(Weapon::getStaticPath())))
//		return true;
//	else
//		return false;
//}
//
//void Knife::shoot()
//{
//	if (Weapon::getRobustness() > 0 && !Weapon::isFreezed())
//	{
//		if (manageDelay())
//			return;
//
//		std::cout << std::boolalpha;
//		std::cout << std::format("Shooting: {}\n",mShootingTexture.isActive());
//		std::cout << std::format("HitBox: {}\n", mHitBoxActive);
//
//		if (!mShootingTexture.isActive() && !mHitBoxActive)
//		{
//			mHitBoxActive = true;
//			mShootingTexture.setCurrentSide(SideOfChar::RIGHT);
//			mShootingTexture.setActive(true);
//			mShootingTexture.runAnimation();
//		}
//		
//		if (mCounterHits >= 4)
//		{
//			mCounterHits = 0;
//			mForRobustness.generateNew();
//			Weapon::setRobustness(Weapon::getRobustness() - mForRobustness.getNumber());
//		}
//
//		mRotateMachine.calculateRadians(Weapon::getWeaponStats().mPos, InputManager::getInstance().getMousePos());
//	}
//}
//
//void Knife::render(SDL_Renderer* pRenderer)
//{
//	if (!Weapon::isFreezed())
//	{
//		if (!mShootingTexture.isActive())
//			brokenChecker(pRenderer);
//		else
//		{
//			mShootingTexture.renderWithRotate(pRenderer, mRotateMachine.getAngle() * 180 / M_PI, InputManager::getInstance().getMousePos());
//			mHitBoxActive = false;
//		}
//	}
//	else
//		brokenChecker(pRenderer);
//}
//
//void Knife::update()
//{
//	if (!mDelayTimer.isRunning())
//		mHitBoxActive = false;
//	if (!Weapon::isFreezed())
//	{
//		TextureManager::getInstance().setPosition(Weapon::getStaticPath(), Weapon::getPos());
//		TextureManager::getInstance().setPosition(Weapon::getBrokenPath(), Weapon::getPos());
//	}
//
//	managePosSlashing();
//}
//
//void Knife::setAsADefaultWeapon()
//{
//	Weapon::defaultParametersWeapons();
//}
//
//void Knife::setAsASpecialWeapon()
//{
//	defaultParametersKnife();
//}
//
//std::vector<int> Knife::isShot(const std::vector<SDL_Rect>& pRects)
//{
//	static std::vector<int> shotIndexes;
//	
//	auto lColliderChecker = [&](SDL_Rect pRect) -> bool
//		{
//			if (mObjects.areColliding(pRect, mHitBoxKnife))
//				return true;
//			return false;
//		};
//
//	if (mHitBoxActive)
//	{
//		for (size_t i = 0; i < pRects.size(); ++i)
//		{
//			if (lColliderChecker(pRects[i]))
//			{
//				if (std::ranges::find(shotIndexes, i) == shotIndexes.end())
//				{
//					shotIndexes.push_back(i);
//					Weapon::setDamage(true);
//					mCounterHits++;
//				}
//				else
//				{
//					shotIndexes.clear();
//					Weapon::setDamage(false);
//				}
//			}
//			else
//				shotIndexes.clear();
//		}
//	}
//	else
//	{
//		shotIndexes.clear();
//		Weapon::setDamage(false);
//	}
//	
//	return shotIndexes;
//}
//
//bool Knife::checkRobustness()
//{
//	if (Weapon::getRobustness() <= 0)
//		return true;
//	return false;
//}
//
//int32_t Knife::checkDamage()
//{
//	if (Weapon::getWeaponStats().mWasDamage)
//	{
//		Weapon::generatePower();
//		return Weapon::getPower();
//	}
//	return 0;
//}
//
//int32_t Knife::getSpeedOfChar(int32_t pHisSpeed)
//{
//	return pHisSpeed * (1 - (Weapon::getWeigth() / 100));
//}
//
//void Knife::manageRotate()
//{
//	mRotateMachine.calculateRadians(Weapon::getWeaponStats().mPos, Weapon::getWeaponStats().mPosMouse);
//}
//
//void Knife::setAllAnimationsNull()
//{
//	mShootingTexture.setActive(false);
//	mShootingTexture.stopAnimation();
//}
//
//bool Knife::manageDelay()
//{
//	if (!mDelayTimer.isRunning())
//		mDelayTimer.startTimer();
//	//std::cout << std::format("Timer: {}\n", mDelayTimer.getDeltaTime(false));
//	if (mDelayTimer.getDeltaTime(false) >= Weapon::getWeaponStats().mDelay)
//	{
//		mDelayTimer.stopTimer();
//		return true;
//	}
//	return false;
//}
//
//void Knife::brokenChecker(SDL_Renderer* pRenderer)
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
//
//void Knife::defaultParametersKnife()
//{
//	Weapon::setRobustness(100);
//	Weapon::setTimeOfDelay(100);
//	Weapon::setQuantityOfBullets(0);
//	Weapon::setOrigQuantityBullets(0);
//	Weapon::setQuantityOfSets(0);
//	Weapon::setReloadingTime(0);
//	Weapon::setOrigReloadTime(0);
//	Weapon::setWeight(2);
//	Weapon::setPower(std::make_pair(0, 3));
//}
//
//void Knife::managePosSlashing()
//{
//	SDL_Rect tmpWeaponRect = Weapon::getCharCollision();
//	Vector2f tmpOffset     = { 60.0f,0.0f };
//
//	float tmpAngle = mRotateMachine.getAngle();
//
//	float rotateDx = tmpOffset.mX * cos(tmpAngle) - tmpOffset.mY * sin(tmpAngle);
//	float rotateDy = tmpOffset.mX * sin(tmpAngle) + tmpOffset.mY * cos(tmpAngle);
//
//	Vector2f tmpPosSlashing = mShootingTexture.getPosition();
//
//	tmpPosSlashing.mX = static_cast<float>(tmpWeaponRect.x + tmpWeaponRect.w / 2.0f + rotateDx - tmpWeaponRect.w / 2.0f) + 10.0f;
//	tmpPosSlashing.mY = static_cast<float>(tmpWeaponRect.y + tmpWeaponRect.h / 2.0f + rotateDy - tmpWeaponRect.h / 2.0f);
//
//	mShootingTexture.setPosition(tmpPosSlashing);
//	mHitBoxKnife.x = static_cast<int>(tmpPosSlashing.mX);
//	mHitBoxKnife.y = static_cast<int>(tmpPosSlashing.mY);
//
//}
//
//void Knife::reload()
//{
//	return;
//}
