#pragma once

#include "Director.h"
#include "Sprite.h"

class Player;
class Stage : public Scene
{
public:
	void init() override;
	void update() override;
	void exit() override;

	Sprite* _game;
	Sprite* _ui;

	Sprite* _stageb;

	Player* _player;

	Sprite* _clear;
	Sprite* _next;

	Sprite* _fail;
	Sprite* _retry;

	Sprite* _grade;

	Sprite* _cut;

	Label* _init1;
	Label* _init2;
	Label* _init3;
	char _initial[3];

	int _initcount;

	bool _touch = false;

	int _end = false;

	bool _cheatclear = false;
	bool _cheatfail = false;

	float _opencount = 0;
	float _enemyinfocount = 0;
};