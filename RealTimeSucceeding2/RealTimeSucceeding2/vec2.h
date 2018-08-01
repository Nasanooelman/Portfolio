#pragma once
#include <math.h>
#include <algorithm>

// This is Jack Lamb's Vector2 Class. I have no credit towards this code whatsoever.
// Thank you to him for letting me use this for my project

class CVector2Int
{
public:
	int x, y;

	CVector2Int(void) : x(0), y(0) {}
	CVector2Int(int xVal, int yVal) : x(xVal), y(yVal) {}
	CVector2Int(const CVector2Int &p) : x(p.x), y(p.y) {}

	void Set(int xVal, int yVal) { x = xVal; y = yVal; }

	//Can perform comparison with CVector2Int, and arithmetic with CVector2Int and Int
	CVector2Int &CVector2Int::operator= (const CVector2Int &p) { x = p.x; y = p.y; return *this; }
	CVector2Int &CVector2Int::operator= (const int &p) { x = y = p; return *this; }
	CVector2Int &CVector2Int::operator- (void) { x = -x; y = -y; return *this; }
	bool CVector2Int::operator== (const CVector2Int &p) const { return (x == p.x) && (y == p.y); }
	bool CVector2Int::operator!= (const CVector2Int &p) const { return (x != p.x) || (y != p.y); }
	const CVector2Int CVector2Int::operator+ (const CVector2Int &p) const { return CVector2Int(x + p.x, y + p.y); }
	const CVector2Int CVector2Int::operator- (const CVector2Int &p) const { return CVector2Int(x - p.x, y - p.y); }
	const CVector2Int CVector2Int::operator* (const CVector2Int &p) const { return CVector2Int(x * p.x, y * p.y); }
	const CVector2Int CVector2Int::operator/ (const CVector2Int &p) const { return CVector2Int(x / p.x, y / p.y); }
	const CVector2Int CVector2Int::operator+ (int p) const { return CVector2Int(x + p, y + p); }
	const CVector2Int CVector2Int::operator- (int p) const { return CVector2Int(x - p, y - p); }
	const CVector2Int CVector2Int::operator* (int p) const { return CVector2Int(x * p, y * p); }
	const CVector2Int CVector2Int::operator/ (int p) const { return CVector2Int(x / p, y / p); }
	CVector2Int &CVector2Int::operator+= (const CVector2Int &p) { x += p.x; y += p.y; return *this; }
	CVector2Int &CVector2Int::operator-= (const CVector2Int &p) { x -= p.x; y -= p.y; return *this; }
	CVector2Int &CVector2Int::operator*= (const CVector2Int &p) { x *= p.x; y *= p.y; return *this; }
	CVector2Int &CVector2Int::operator/= (const CVector2Int &p) { x /= p.x; y /= p.y; return *this; }
	CVector2Int &CVector2Int::operator+= (int p) { x += p; y += p; return *this; }
	CVector2Int &CVector2Int::operator-= (int p) { x -= p; y -= p; return *this; }
	CVector2Int &CVector2Int::operator*= (int p) { x *= p; y *= p; return *this; }
	CVector2Int &CVector2Int::operator/= (int p) { x /= p; y /= p; return *this; }

};

class CVector2
{
public:
	float x, y;

	CVector2(void) : x(0), y(0) {}
	CVector2(float xVal, float yVal) : x(xVal), y(yVal) {}
	CVector2(const CVector2 &v) : x(v.x), y(v.y) {}

	void Set(float xVal, float yVal) { x = xVal; y = yVal; }

	float Length() const { return (float)sqrt((x * x) + (y * y)); }
	float LengthSquared() const { return (x * x) + (y * y); }
	float Distance(const CVector2 &v) const { return (float)sqrt(((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y))); }
	float Dot(const CVector2 &v) const { return (x * v.x) + (y * v.y); }
	float Cross(const CVector2 &v) const { return (x * v.y) + (y * v.x); }

	CVector2 &Normal()
	{
		float len = Length();
		Set(x / len, y / len);
		return *this;
	}

	CVector2 &Normalise()
	{
		if (Length() > 0)
		{
			float length = LengthSquared();
			x /= length;
			y /= length;
			return *this;
		}

		x = y = 0;
		return *this;
	}

	//Interpolates the current vector to the given one, based on the given step value
	CVector2 &Interpolate(const CVector2 &newVec2, const float &step)
	{
		x = ((1 - step) * x + step * newVec2.x);
		y = ((1 - step) * y + step * newVec2.y);
		return *this;
	}

	//Converts to a CVector2Int
	CVector2Int toInt() const
	{
		return CVector2Int((int)x, (int)y);
	}

	//Can perform comparison with CVector2, and arithmetic with CVector2, CVector2Int and Int
	CVector2 &CVector2::operator= (const CVector2 &v) { x = v.x; y = v.y; return *this; }
	CVector2 &CVector2::operator= (const float &f) { x = y = f; return *this; }
	CVector2 &CVector2::operator- (void) { x = -x; y = -y; return *this; }
	bool CVector2::operator== (const CVector2 &v) const { return (x == v.x) && (y == v.y); }
	bool CVector2::operator!= (const CVector2 &v) const { return (x != v.x) || (y != v.y); }
	const CVector2 CVector2::operator+ (const CVector2 &v) const { return CVector2(x + v.x, y + v.y); }
	const CVector2 CVector2::operator- (const CVector2 &v) const { return CVector2(x - v.x, y - v.y); }
	const CVector2 CVector2::operator* (const CVector2 &v) const { return CVector2(x * v.x, y * v.y); }
	const CVector2 CVector2::operator/ (const CVector2 &v) const { return CVector2(x / v.x, y / v.y); }
	const CVector2 CVector2::operator+ (const CVector2Int &v) const { return CVector2(x + v.x, y + v.y); }
	const CVector2 CVector2::operator- (const CVector2Int &v) const { return CVector2(x - v.x, y - v.y); }
	const CVector2 CVector2::operator* (const CVector2Int &v) const { return CVector2(x * v.x, y * v.y); }
	const CVector2 CVector2::operator/ (const CVector2Int &v) const { return CVector2(x / v.x, y / v.y); }
	const CVector2 CVector2::operator+ (float v) const { return CVector2(x + v, y + v); }
	const CVector2 CVector2::operator- (float v) const { return CVector2(x - v, y - v); }
	const CVector2 CVector2::operator* (float v) const { return CVector2(x * v, y * v); }
	const CVector2 CVector2::operator/ (float v) const { return CVector2(x / v, y / v); }
	CVector2 &CVector2::operator+= (const CVector2 &v) { x += v.x; y += v.y; return *this; }
	CVector2 &CVector2::operator-= (const CVector2 &v) { x -= v.x; y -= v.y; return *this; }
	CVector2 &CVector2::operator*= (const CVector2 &v) { x *= v.x; y *= v.y; return *this; }
	CVector2 &CVector2::operator/= (const CVector2 &v) { x /= v.x; y /= v.y; return *this; }
	CVector2 &CVector2::operator+= (float v) { x += v; y += v; return *this; }
	CVector2 &CVector2::operator-= (float v) { x -= v; y -= v; return *this; }
	CVector2 &CVector2::operator*= (float v) { x *= v; y *= v; return *this; }
	CVector2 &CVector2::operator/= (float v) { x /= v; y /= v; return *this; }

};