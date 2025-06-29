#pragma once
#include <vector>
#include <string>

#include "Singleton.h"
#include "Bullets.h"

class Weapon;

class WeaponManager : public Singleton<WeaponManager>
{
public:
	void appendWeapon(std::unique_ptr<Weapon> pWeapon, std::string_view pName);
	void appendRangeOfWeapon(std::vector<std::pair<std::string, std::unique_ptr<Weapon>>>& pRange);
	void removeWeapon(std::string_view pName);

	Weapon* getWeapon(std::string_view pName);

	void assignBullets(std::string_view pName, std::unique_ptr<Bullets> pBullets);
	Bullets* getBullets(std::string_view pName);

	void throwWeapon();
	void takeWeapon(SDL_Rect pCharCollision);

private:
	struct WeaponRelationship
	{
		std::unique_ptr<Weapon> mWeapon;
		std::unique_ptr<Bullets> mBullets;

		WeaponRelationship() = default;
		~WeaponRelationship() = default;

		WeaponRelationship(const WeaponRelationship&) = delete;
		WeaponRelationship& operator=(const WeaponRelationship&) = delete;

		WeaponRelationship(WeaponRelationship&&) = default;
		WeaponRelationship& operator=(WeaponRelationship&&) = default;

	} mWR;

	std::unordered_map<std::string, WeaponRelationship> mStorageWeapons;

	friend class Singleton<WeaponManager>;
};

