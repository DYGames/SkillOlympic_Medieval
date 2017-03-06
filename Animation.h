#pragma once

#include "DXUT.h"
#include <vector>
#include <functional>

class Texture;
class Sprite;

class Animation
{
public:
	Sprite* _target;

	std::function<void()> _endfunc;

	float _maxdelay = 0;
	float _delay = 0;
	
	int _idx = 0;

	bool _loop = false;
	bool _erase = false;
	bool _run = false;

	std::vector<Texture*> _clips;

	void initAnimation(Sprite* t, float d, bool l, bool e = false);

	void addClips(std::wstring str);

	void removeClipAll();

	void update();

};