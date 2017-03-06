#pragma once

#include "DXUT.h"

class Vec2 : public D3DXVECTOR2
{
public:
	Vec2(D3DXVECTOR2 v) : D3DXVECTOR2(v) {}
	Vec2() { x = y = 0; }
	Vec2(float xx, float yy){ x = xx, y = yy; }

	float distance(Vec2 v)
	{
		float dx = v.x - x;
		float dy = v.y - y;
		return sqrt(dx * dx + dy * dy);
	}

};

class Rect : public RECT
{
public:
	Rect(RECT r) : RECT(r){}
	Rect() { left = right = top = bottom = 0; }
	Rect(float lleft, float rright, float ttop, float bbottom){ left = lleft, right = rright, top = ttop, bottom = bbottom; }

	bool containsPoint(Vec2 v)
	{
		if (left <= v.x && v.x <= right)
			if (top <= v.y && v.y <= bottom)
				return true;
		return false;
	}

	bool intersectRect(Rect r)
	{
		if (left < r.right &&
			top < r.bottom &&
			right > r.left &&
			bottom > r.top)
			return true;
		return false;
	}


};

class Time
{
public:
	static float dt;
};

class Input
{
public:

	static Vec2 mouseLocation()
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(DXUTGetHWND(), &pt);
		return Vec2(pt.x, pt.y);
	}
};
