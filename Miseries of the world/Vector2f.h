#pragma once
#include <utility>
#include <ostream>
#include <math.h>

class Vector2f
{
public:
	Vector2f(const float pX, const float pY);
	
	inline Vector2f operator+(const Vector2f& pOther) const;
	inline Vector2f operator+=(const Vector2f& pOther);
	inline Vector2f operator+(const float pScalar) const;

	inline Vector2f operator-(const Vector2f& pOther) const;
	inline Vector2f operator-=(const Vector2f& pOther);
	inline Vector2f operator-(const float pScalar) const;

	inline Vector2f operator*(const Vector2f pOther) const;
	inline Vector2f operator*=(const Vector2f& pOther);
	inline Vector2f operator*(const float pScalar) const;
	
	inline Vector2f operator/(const Vector2f pOther) const;
	inline Vector2f operator/=(const Vector2f& pOther);
	inline Vector2f operator/(const float pScalar) const;

	inline bool operator==(const Vector2f& pOther) const;
	inline bool operator!=(const Vector2f& pOther) const;
	
	friend std::ostream& operator<<(std::ostream& os, const Vector2f& vec)
	{
		return os << "(" << vec.mX << " , " << vec.mY << ")";
	}

	inline float length() const;
	Vector2f normalize() const;
	inline float distanceTo(const Vector2f& pOther) const;
	static float dotProduct(const Vector2f& pFirst, const Vector2f& pSecond)
	{
		return (pFirst.mX * pSecond.mX) + (pFirst.mY * pSecond.mY);
	}

	float mX, mY;
	float mVX, mVY;
};


