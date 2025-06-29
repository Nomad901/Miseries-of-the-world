#pragma once
#include "FireMode.h"

enum class Mode
{
	SEQUENCE = 0,
	SINGLE = 1
};

class SingleOrSequence : public FireMode
{
public:
	SingleOrSequence() = default;
	~SingleOrSequence() override = default;

	void shoot(SDL_Rect pCharRect, SDL_Rect pWeaponRect, bool pWasReload) override;
	void update(SDL_Renderer* pRenderer, const Vector2f& pPos) override;
	void render() override;

	void setAsSpecial() override;
	void setMode(Mode pMode);

protected:
	bool manageDelay() override;

private:
	RotateMachine mRotateMachine;
	Timer mTimer;

	Mode mMode{ Mode::SEQUENCE };
};

