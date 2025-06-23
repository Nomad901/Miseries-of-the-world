#pragma once
#include "Singleton.h"
#include "TextureManager.h"
#include "Timer.h"
#include "Assets.h"
#include "InputManager.h"

enum class SideOfChar
{
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3
};
enum class HorVer
{
	VERTICAL = 0,
	HORIZONTAL = 1
};
enum class TypeWait
{
	GENERAL = 0,
	WAIT = 1
};

class AnimatedTexture : public TextureManager
{
public:
	AnimatedTexture() = default;
	~AnimatedTexture();

	void appendAnimation(TypeWait pType, SDL_Renderer* pRenderer, const PATH& pPath, const Vector2f& pPos, 
						 const int pW, const int pH, HorVer pSide);
	//than bigger - then slower
	inline void setIntensity(const float pIntensity)   { mIntensity = pIntensity; }
	inline void setCurrentSide(const SideOfChar pSide) { mCurrentSide = pSide;    }
	inline void setActive(const bool pActive)		   { mActive = pActive;       }
	inline void waitWithAnim(const bool pWaitAnim)     { mWaitAnim = pWaitAnim;   }
	void setSides(const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers);
	void setPosition(const Vector2f& pPos);
	
	Vector2f getPosition() const { return { static_cast<float>(mDstRect.x), static_cast<float>(mDstRect.y) }; }
	bool isActive() const { return mActive; }
	bool isEnded() const;
	void setEnded(bool pEnded);

	SDL_Rect getAnimRect() const noexcept;

	void stopAnimation();
	void runAnimation();
	void runAnimationOnlyOnce();

	void render(SDL_Renderer* pRenderer);
	void renderWithRotate(SDL_Renderer* pRenderer, double pAngle, const Vector2f& pMousePos);
	// ticks for animation. like every tick - will be playing each frame 
	void nullTicks();

private:
	void dividerFrames(SDL_Renderer* pRenderer);
	void createTexturesFromFrames(SDL_Renderer* pRenderer);

private:
	bool mWaitAnim{ false };
	bool mAnimating{ false };
	bool mActive{ false };
	bool mOnceAnim{ false };
	bool mEnded{ false };

	float mIntensity{ 0.0f };
	int32_t mCounter{ 0 };
	Timer mTimer;

	SDL_Rect mDstRect{50,50,50,50};
	std::vector<SDL_Rect> mSprites;
	std::unordered_map<int, std::pair<SDL_Texture*, SDL_Rect>> mStorageFrames;
	std::unordered_map<int, std::pair<SDL_Texture*, SDL_Rect>> mStorageWaitFrames;
	std::unordered_map<SideOfChar, std::vector<uint32_t>> mSteps;

	HorVer mHorVer{ HorVer::HORIZONTAL };
	SideOfChar mCurrentSide{ SideOfChar::UP };

	PATH mPath{ std::filesystem::current_path() };
};