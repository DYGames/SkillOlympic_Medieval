#pragma once

#include "Director.h"
#include "Sprite.h"

class Main : public Scene
{
public:
	void init() override;
	void update() override;
	void exit() override;

	void Load();

	void Buy(bool suc);

	Sprite* _game;
	Sprite* _ui;

	Sprite* _black;

	Sprite* _mainb;
	Sprite* _mainstart;

	Sprite* _stageb;
	Sprite* _s1b;
	Sprite* _s2b;
	Sprite* _s3b;
	Sprite* _s1;
	Sprite* _s2;
	Sprite* _s3;
	Sprite* _s4;

	Sprite* _next;
	Sprite* _shop;

	Sprite* _load;

	Sprite* _shopback;
	Sprite* _owner;
	Sprite* _potion;
	Sprite* _mana;
	Sprite* _dmg;
	Sprite* _hlth;
	Sprite* _up;
	Sprite* _pop;
	Sprite* _buy;
	Sprite* _cancle;

	Sprite* _lock2;
	Sprite* _lock3;
	Sprite* _lock4;

	Sprite* _coin;
	Label* _money;

	int _buycount;

	bool _touch = false;
};