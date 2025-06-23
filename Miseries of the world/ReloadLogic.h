#pragma once
#include <vector>

#include <SDL.h>

struct ReloadLogic
{
	virtual ~ReloadLogic() = default;

	virtual void reload() = 0;
	virtual void neededToReload() = 0;
	virtual void setRelodingTime(int32_t pReloadingTime) = 0;
	virtual int32_t getReloadingTime() = 0;
};

