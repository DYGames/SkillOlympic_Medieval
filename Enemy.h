#pragma once

#include "Sprite.h"
#include "MissionMng.h"
#include "GameMng.h"

class Player;

class Enemy : public Sprite
{
public:
	enum ENEMYSTATE
	{
		IDLE_LEFT,
		IDLE_RIGHT,
		IDLE_TOP,
		IDLE_BOTTOM,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_TOP,
		MOVE_BOTTOM,
		ATK_LEFT,
		ATK_RIGHT,
		ATK_TOP,
		ATK_BOTTOM,
		DIE,
	};

	int _hp;
	int _maxhp;
	int _attackdmg;
	ENEMYSTATE _state;
	Player* _player;
	Vec2 _dir;
	Vec2 _oripos;

	Sprite* _hpback;
	Sprite* _hpbar;
	Sprite* _aggro;

	float _maxmdelay;
	float _mdelay;

	float _maxadelay;
	float _adelay;

	bool _mamonactive;

	bool _skill1hiton;

	float _skullspawncount;

	bool _brzspawn = false;
	bool _silspawn = false;
	bool _gldspawn = false;

	Enemy(std::wstring name, Player* player);

	void Hitted(int dmg, Vec2 hitdir);

	void Animate();

	void update() override;

	void Attack();

	void RangeAttack();
};