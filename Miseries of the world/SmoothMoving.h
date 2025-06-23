#pragma once
#include <SDL.h>

#include "Vector2f.h"
#include "Physics.h"

class SmoothMoving : public Physics
{
public:
	SmoothMoving() = default;

	void moving(Vector2f& pPosition, float pTime);
	void stopping();
	
	

	void setTargetVelocity(Vector2f pVelocity);
	Vector2f getTargetVelocity();

private:
	Vector2f mTargetVelocity{ 2.0f, 2.0f };

};

