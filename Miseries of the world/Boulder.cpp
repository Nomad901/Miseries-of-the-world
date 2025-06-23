//#include "Boulder.h"
//#include "Timer.h"
//#include "BulletsPool.h"
//
//Boulder::Boulder(SDL_Renderer* pRenderer,
//				 const Vector2f& pPos, int pW, int pH, std::pair<int32_t, int32_t> pPower, int32_t pDelay,
//				 const PATH& pStaticPath, SDL_Rect pChar)
//	: mRenderer{ pRenderer }
//{
//	Weapon::takeWeapon(pChar);
//	Weapon::setMousePos(pPos);
//	Weapon::setAllParameteres(pPos, pW, pH, 0, 0, 100, pPower, 0, 20);
//	Weapon::setTimeOfDelay(pDelay);
//	Weapon::setAllPaths(pStaticPath, std::filesystem::current_path(), 
//						std::filesystem::current_path(), std::filesystem::current_path());
//
//	SDL_Rect tmpRect = { static_cast<int32_t>(pPos.mX), static_cast<int32_t>(pPos.mY), pW, pH };
//	TextureManager::getInstance().appendTexture(pRenderer, pStaticPath, tmpRect);
//
//	mTimer.setDimensionOfTime(Dimension::MILISECONDS);
//
//	mBullets = std::make_unique<BulletsPool>();
//	mBullets->init(500, mRenderer, std::filesystem::current_path() / "Assets" / "photos and ttf" / "boulder.png", pPos, 50, 50, 10);
//}
//
//bool Boulder::WeaponIsInView(SDL_Rect pCharCollision)
//{
//	if (mObjects.areColliding(pCharCollision, TextureManager::getInstance().getRect(Weapon::getStaticPath())))
//		return true;
//	else
//		return false;
//}
//
//void Boulder::shoot()
//{
//	if (!Weapon::isFreezed())
//	{
//		if (manageDelay())
//			return;
//
//		mRotateMachine.calculateRadians(Weapon::getPos(),InputManager::getInstance().getMousePos());
//
//		mBullets->makeBulletActive();
//		mBullets->manageLastBulletInside()->setSpeed(10);
//		auto tmpPos = Weapon::getWeaponStats().mPos;
//		mBullets->manageLastBulletInside()->shootBullet({ tmpPos.mX + Weapon::getWeaponStats().mW - 40, tmpPos.mY }, InputManager::getInstance().getMousePos(),
//														  mRotateMachine.getAngle(), TextureManager::getInstance().getRect(Weapon::getStaticPath()),
//														{ static_cast<float>(TextureManager::getInstance().getRect(Weapon::getStaticPath()).w / 2 - 10),-5 },
//														  Weapon::getCharCollision().w, Weapon::getCharCollision().h);
//	}
//}
//
//void Boulder::render(SDL_Renderer* pRenderer)
//{
//	if (!Weapon::isFreezed())
//	{
//		SDL_RenderCopyEx(pRenderer, TextureManager::getInstance().getTexture(Weapon::getStaticPath()), nullptr,
//						 &TextureManager::getInstance().getRect(Weapon::getStaticPath()), mRotateMachine.getAngle() * 180 / M_PI, nullptr,
//						 Weapon::getWeaponStats().mPosMouse.mX >= Weapon::getWeaponStats().mPos.mX ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
//	}
//	else
//	{
//		SDL_RenderCopy(pRenderer, TextureManager::getInstance().getTexture(Weapon::getStaticPath()), nullptr,
//					   &TextureManager::getInstance().getRect(Weapon::getStaticPath()));
//	}
//	mBullets->update();
//}
//
//void Boulder::update()
//{
//	if (!Weapon::isFreezed())
//		TextureManager::getInstance().setPosition(Weapon::getStaticPath(), Weapon::getPos());
//}
//
//void Boulder::setAsADefaultWeapon()
//{
//	Weapon::defaultParametersWeapons();
//}
//
//void Boulder::setAsASpecialWeapon()
//{
//	defaultParametersBoulder();
//}
//
//std::vector<int> Boulder::isShot(const std::vector<SDL_Rect>& pRects)
//{
//	static std::vector<int> shotIndexes;
//
//	auto lIsColiding = [&](SDL_Rect pRect) -> std::pair<bool, int32_t>
//		{
//			for (size_t i = 0; i < mBullets->getSizeActiveBullets(); ++i)
//			{
//				if (mBullets->manageBulletIndise(i)->isColliding(pRect))
//					return std::make_pair(true, i);
//			}
//			return std::make_pair(false, 0);
//		};
//
//	if (mBullets->getSizeActiveBullets() != 0 && mBullets->getSizeBullets() != 0)
//	{
//		for (size_t i = 0; i < pRects.size(); ++i)
//		{
//			auto it = lIsColiding(pRects[i]);
//			if (it.first)
//			{
//				if (std::ranges::find(shotIndexes, i) == shotIndexes.end())
//				{
//					shotIndexes.push_back(i);
//					Weapon::setDamage(true);
//				}
//				else
//				{
//					Weapon::setDamage(false);
//					mBullets->destroyBullet(it.second);
//					shotIndexes.clear();
//				}
//			}
//			else
//				shotIndexes.clear();
//		}
//	}
//	return shotIndexes;
//}
//
//bool Boulder::checkRobustness()
//{
//	return false;
//}
//
//int32_t Boulder::checkDamage()
//{
//	if (Weapon::getWeaponStats().mWasDamage)
//	{
//		Weapon::generatePower();
//		return Weapon::getPower();
//	}
//	return 0;
//}
//
//int32_t Boulder::getSpeedOfChar(int32_t pHisSpeed)
//{
//	return pHisSpeed * (1 - (Weapon::getWeigth() / 100));
//}
//
//void Boulder::manageRotate()
//{
//	mRotateMachine.calculateRadians(Weapon::getWeaponStats().mPos, Weapon::getWeaponStats().mPosMouse);
//}
//
//bool Boulder::manageDelay()
//{
//	if (!mTimer.isRunning())
//		mTimer.startTimer();
//	if (mTimer.getDeltaTime(false) <= Weapon::getWeaponStats().mDelay)
//		return true;
//	else
//		mTimer.stopTimer();
//	return false;
//}
//
//void Boulder::defaultParametersBoulder()
//{
//	Weapon::setRobustness(100);
//	Weapon::setTimeOfDelay(500);
//	Weapon::setQuantityOfBullets(0);
//	Weapon::setOrigQuantityBullets(0);
//	Weapon::setQuantityOfSets(0);
//	Weapon::setReloadingTime(0);
//	Weapon::setOrigReloadTime(0);
//	Weapon::setWeight(1);
//	Weapon::setPower(std::make_pair(0, 2));
//}
//
//void Boulder::reload()
//{
//	return;
//}
