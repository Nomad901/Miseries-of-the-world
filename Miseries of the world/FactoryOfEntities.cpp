#include "FactoryOfEntities.h"
#include "Weapon.h"
#include "FactoryObjects.h"
#include "WeaponManager.h"

FactoryOfEntities::FactoryOfEntities()
{
	WeaponManager::init();
}

FactoryOfEntities::~FactoryOfEntities()
{
	WeaponManager::shutDown();
}

void FactoryOfEntities::setName(std::string_view pName)
{
	mName = pName;
}

std::string FactoryOfEntities::getName() const noexcept
{
	return mName;
}

void FactoryOfEntities::setVisibility(bool pVisibility)
{
	mVisible = pVisibility;
}

bool FactoryOfEntities::isVisible() const noexcept
{
	return mVisible;
}

bool FactoryOfEntities::isGripping(std::string_view pName)
{
	return WeaponManager::getInstance().getWeapon(pName) != nullptr;
}

bool FactoryOfEntities::isGripping(std::unique_ptr<FactoryObjects> pObject)
{
	return pObject == mObject ? true : false;
}

bool FactoryOfEntities::isGripping() const noexcept
{
	return mIsGripping;
}

bool FactoryOfEntities::isAlive() const noexcept
{
	return mIsAlive;
}

void FactoryOfEntities::makeAlive(bool pAlive)
{
	mIsAlive = pAlive;
}

int FactoryOfEntities::getHealth() const noexcept
{
	return mHealth;
}

void FactoryOfEntities::setHealth(int pHealth)
{
	mHealth = pHealth;
}

int FactoryOfEntities::getLives() const noexcept
{
	return mLives;
}

void FactoryOfEntities::setLives(int pLives)
{
	mLives = pLives;
}

float FactoryOfEntities::getSpeed() const noexcept
{
	return mSpeed;
}

void FactoryOfEntities::setSpeed(const float pSpeed)
{
	mSpeed = pSpeed;
}

Vector2f FactoryOfEntities::getPos() const noexcept
{
	return mPosition;
}	

void FactoryOfEntities::setPos(Vector2f pPos)
{
	mPosition = pPos;
}

void FactoryOfEntities::makeParent(std::unique_ptr<FactoryOfEntities> pParent)
{
	mParent = std::move(pParent);
}

void FactoryOfEntities::takeObject(std::unique_ptr<FactoryObjects> pObject)
{
	if (pObject == nullptr)
	{
		mIsGripping = false;
		mObject = nullptr;
	}
	else
	{
		mIsGripping = true;
		mObject = std::move(pObject);	
	}
}
void FactoryOfEntities::takeWeapon(std::unique_ptr<Weapon> pWeapon)
{
	std::string tmpName = "Weapon1";
	WeaponManager::getInstance().appendWeapon(std::move(pWeapon), tmpName);
	int lastNumber = stoi(std::to_string(tmpName[tmpName.size() - 1]))+1;
	tmpName.erase(tmpName.size() - 1);
	tmpName += std::to_string(lastNumber);
}
