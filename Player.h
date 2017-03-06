#pragma once

#include "DXUT.h"
#include "Sprite.h"
#include "Tile.h"
#include "Enemy.h"


class Player : public Sprite
{
public:
	enum PLAYERSTATE
	{
		IDLE_LEFT,
		IDLE_RIGHT,
		IDLE_TOP,
		IDLE_BOTTOM,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_TOP,
		MOVE_BOTTOM,
		RUN_LEFT,
		RUN_RIGHT,
		RUN_TOP,
		RUN_BOTTOM,
		ATK_LEFT,
		ATK_RIGHT,
		ATK_TOP,
		ATK_BOTTOM,
		DFC_LEFT,
		DFC_RIGHT,
		DFC_TOP,
		DFC_BOTTOM,
		TURN_LEFTTOTOP,
		TURN_RIGHTTOTOP,
		TURN_BOTTOMTOLEFT,
		TURN_TOPTOLEFT,
		TURN_LEFTTOBOTTOM,
		TURN_RIGHTTOBOTTOM,
		TURN_TOPTORIGHT,
		TURN_BOTTOMTORIGHT,
		DIE,
		DEFAULT,
	};

	Vec2 _dir;
	PLAYERSTATE _state;
	PLAYERSTATE _prevstate;
	float _mspeed;
	float _maxmdelay;
	float _mdelay;

	float _maxhp;
	float _hp;
	float _attackdmg;
	int _mana;

	int _getMoney;

	bool _god = false;

	bool _avoid = false;
	bool _defence = false;

	bool _rtouch = false;

	bool _skill1on = false;

	Player();

	void update() override;

	void MoveDir(Vec2 dir);

	void Hitted(int dmg);

	void Animate();

	void UseSkill(int t);

	float _skill1cool;
	float _skill2cool;
	float _skill3cool;
};