#pragma once
#include "TextureManager.h"
#include "Vector2f.h"
#include "RotateMachine.h"

class Bullets
{
public:
    Bullets(SDL_Renderer* pRenderer, 
            const PATH& pPath, const Vector2f& pPos,
            int32_t pW, int32_t pH, int32_t pSpeed);
    ~Bullets() = default;

    void shootBullet(const Vector2f& pPlayerPos, const Vector2f& pMousePos, SDL_Rect pWeaponRect,
                     double pAngle, const Vector2f& pOffset, int32_t pW, int32_t pH);

    bool isColliding(SDL_Rect pRect);
    bool isActive();
    bool checkBoundaries();
    
    SDL_Rect& getShape();

    Vector2f getPos() const noexcept;
    void setPos(const Vector2f& pPos);

    int32_t getSpeed() const noexcept;
    void setSpeed(int32_t pSpeed);

    PATH getPath();
    void setPath(const PATH& pPath);

    void render();
    void update();

private:

    void updateAttachedRect(SDL_Rect pWeaponRect);

private:
    bool mActive{ false };

    RotateMachine mRotateMachine;

    float mAttachedAngle{ 0.0f };
	int32_t mSpeed{ 0 };
    Vector2f mAttachedOffset{ 0.0f, 0.0f };
	Vector2f mPos{ 0.0f, 0.0f };
    Vector2f mMousePos{ 0.0f,0.0f };
    PATH mPath;

    SDL_Rect mRect{ 0,0,0,0 };
	SDL_Renderer* mRenderer{ nullptr };

};

