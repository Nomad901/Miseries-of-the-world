#include "RotateMachine.h"

void RotateMachine::calculateDirection(const Vector2f& pPos1, const Vector2f& pPos2, int32_t pW, int32_t pH)
{
    mDirection = { pPos2.mX - (pPos1.mX + pW / 2),
                   pPos2.mY - (pPos1.mY + pH / 2) };
}

void RotateMachine::calculateLength(const Vector2f& pPos)
{
    mLength = sqrt((pPos.mX * pPos.mX) + (pPos.mY * pPos.mY));
}

void RotateMachine::calculateSpeed(const Vector2f& pDirection, double pLength, int32_t pSpeed)
{
    if (pLength > 0)
        mSpeed = { static_cast<float>((pDirection.mX / pLength) * pSpeed), static_cast<float>((pDirection.mY / pLength) * pSpeed) };
    else
        mSpeed = { 0,0 };
}

void RotateMachine::calculateRadians(const Vector2f& pPos)
{
    mAngle = atan2(pPos.mX, pPos.mY);
}

void RotateMachine::calculateDegrees(const Vector2f& pPos)
{
    mAngle = atan2(pPos.mX, pPos.mY) * 180 / M_PI;
}

void RotateMachine::calculateRadians(const Vector2f& pPos1, const Vector2f pPos2)
{
    mAngle = atan2(pPos2.mY - pPos1.mY, pPos2.mX - pPos1.mX);
}

void RotateMachine::calculateDegrees(const Vector2f& pPos1, const Vector2f pPos2)
{
    mAngle = atan2(pPos2.mY - pPos1.mY, pPos2.mX - pPos1.mX) * 180 / M_PI;
}

void RotateMachine::convertRadiansIntoDegrees(double pAngle)
{
    mAngle = pAngle * 180 / M_PI;
}

void RotateMachine::convertDegreesIntoRadians(double pAngle)
{
    mAngle = pAngle * M_PI / 180;
}

void RotateMachine::setAngle(double pAngle) 
{
    mAngle = pAngle;
}

void RotateMachine::setLength(double pLength)
{
    mLength = pLength;
}

void RotateMachine::setDirection(const Vector2f& pDirection) 
{
    mDirection = pDirection;
}

void RotateMachine::setSpeed(const Vector2f& pSpeed) 
{
    mSpeed = pSpeed;
}

double RotateMachine::getAngle() const noexcept
{
    return mAngle;
}

double RotateMachine::getLength() const noexcept
{
    return mLength;
}

Vector2f RotateMachine::getDirection() const noexcept
{
    return mDirection;
}

Vector2f RotateMachine::getSpeed() const noexcept
{
    return mSpeed;
}
