#include "Vector2f.h"
Vector2f::Vector2f(const float pX, const float pY)
	:mX(pX), mY(pY)
{}

inline Vector2f Vector2f::operator+(const Vector2f& pOther) const
{
	return Vector2f(mX + pOther.mX, mY + pOther.mY);
}
inline Vector2f Vector2f::operator+=(const Vector2f& pOther)
{
	mX += pOther.mX;
	mY += pOther.mY;
	return *this;
}
inline Vector2f Vector2f::operator+(const float pScalar) const
{
	return Vector2f(mX + pScalar, mY + pScalar);
}

inline Vector2f Vector2f::operator-(const Vector2f& pOther) const
{
	return Vector2f(mX - pOther.mX, mY - pOther.mY);
}
inline Vector2f Vector2f::operator-=(const Vector2f& pOther)
{
	mX -= pOther.mX;
	mY -= pOther.mY;
	return *this;
}
inline Vector2f Vector2f::operator-(const float pScalar) const
{
	return Vector2f(mX - pScalar, mY - pScalar);
}

inline Vector2f Vector2f::operator*(const Vector2f pOther) const
{
	return Vector2f(mX * pOther.mX, mY * pOther.mY);
}
inline Vector2f Vector2f::operator*=(const Vector2f& pOther)
{
	mX *= pOther.mX;
	mY *= pOther.mY;
	return *this;
}
inline Vector2f Vector2f::operator*(const float pScalar) const
{
	return Vector2f(mX * pScalar, mY * pScalar);
}

inline Vector2f Vector2f::operator/(const Vector2f pOther) const
{
	return Vector2f(mX / pOther.mX, mY / pOther.mY);
}
inline Vector2f Vector2f::operator/=(const Vector2f& pOther)
{
	mX /= pOther.mX;
	mY /= pOther.mY;
	return *this;
}
inline Vector2f Vector2f::operator/(const float pScalar) const
{
	return Vector2f(mX / pScalar, mY / pScalar);
}

inline bool Vector2f::operator==(const Vector2f& pOther) const
{
	return mX == pOther.mX && mY == pOther.mY ? true : false;
}
inline bool Vector2f::operator!=(const Vector2f& pOther) const
{
	return mX != pOther.mX || mY != pOther.mY ? true : false;
}

inline float Vector2f::length() const
{
	return std::sqrt((mX * mX) + (mY * mY));
}
Vector2f Vector2f::normalize() const
{
	const float varLenght = length();
	if (varLenght > 0)
		return Vector2f(mX / varLenght, mY / varLenght);
	return Vector2f(0, 0);
}
inline float Vector2f::distanceTo(const Vector2f& pOther) const
{
	return std::sqrt((mX - pOther.mX) * (mX - pOther.mX) + (mY - pOther.mY) * (mY - pOther.mY));
}
