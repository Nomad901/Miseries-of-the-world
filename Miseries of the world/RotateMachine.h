#pragma once
#include <math.h>

#include "Loging.h"
#include "Vector2f.h"

class RotateMachine
{	
public:
	void calculateDirection(const Vector2f& pPos1, const Vector2f& pPos2, int32_t pW, int32_t pH);
	void calculateLength(const Vector2f& pPos);

	void calculateSpeed(const Vector2f& pDirection, double pLength, int32_t pSpeed);

	void calculateRadians(const Vector2f& pPos);
	void calculateDegrees(const Vector2f& pPos);
	//pos2 - pos1
	void calculateRadians(const Vector2f& pPos1, const Vector2f pPos2);
	//pos2 - pos1
	void calculateDegrees(const Vector2f& pPos1, const Vector2f pPos2);

	void convertRadiansIntoDegrees(double pAngle);
	void convertDegreesIntoRadians(double pAngle);

	void setAngle(double pAngle);
	void setLength(double pLength);
	void setDirection(const Vector2f& pDirection);
	void setSpeed(const Vector2f& pSpeed);

	double getAngle() const noexcept;
	double getLength() const noexcept;
	Vector2f getDirection() const noexcept;
	Vector2f getSpeed() const noexcept;

private:
	double mAngle{ 0.0f };
	double mLength{ 0.0f };
	Vector2f mDirection{ 0.0f,0.0f };
	Vector2f mSpeed{ 0.0f,0.0f };

};

