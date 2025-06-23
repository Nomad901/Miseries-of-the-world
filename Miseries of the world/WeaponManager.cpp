#include "WeaponManager.h"
#include "Weapon.h"
#include "Bullets.h"

void WeaponManager::appendWeapon(std::unique_ptr<Weapon> pWeapon, std::string_view pName)
{
	mWR.mWeapon  = std::move(pWeapon);
	mWR.mBullets = nullptr;
	mStorageWeapons.insert_or_assign(std::string(pName), std::move(mWR));
}

void WeaponManager::appendRangeOfWeapon(std::vector<std::pair<std::string, std::unique_ptr<Weapon>>>& pRange)
{
	for (auto& [first,second] : pRange)
	{
		mWR.mWeapon  = std::move(second);
		mWR.mBullets = nullptr;
		mStorageWeapons.insert_or_assign(std::string(first), std::move(mWR));
	}
}

void WeaponManager::removeWeapon(std::string_view pName)
{
	auto it = mStorageWeapons.find(std::string(pName));
	if (it != mStorageWeapons.end())
		mStorageWeapons.erase(it);
	else
		LOG("There is no such a name!");
}

Weapon* WeaponManager::getWeapon(std::string_view pName)
{
	if (mStorageWeapons.contains(std::string(pName)))
		return mStorageWeapons[std::string(pName)].mWeapon.get();
	LOG("There is no such a name!");
	return nullptr;
}

void WeaponManager::assignBullets(std::string_view pName, std::unique_ptr<Bullets> pBullets)
{
	if (mStorageWeapons.contains(std::string(pName)))
		mStorageWeapons[std::string(pName)].mBullets = std::move(pBullets);
	else
		LOG("There is no such a name!");
}

Bullets* WeaponManager::getBullets(std::string_view pName)
{
	if (mStorageWeapons.contains(std::string(pName)))
		return mStorageWeapons[std::string(pName)].mBullets.get();
	LOG("There is no such a name!");
	return nullptr;
}

