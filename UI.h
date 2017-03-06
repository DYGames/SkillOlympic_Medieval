#pragma once

#include "Sprite.h"
#include "Node.h"
#include "MissionMng.h"
#include "Player.h"

class UI
{
public:
	static UI* _uinstance;
	static UI* getInstance()
	{
		if (!_uinstance)
			_uinstance = new UI();
		return _uinstance;
	}

	Sprite* _parent;

	Player* _player;

	Sprite* _enemyinfo;
	Sprite* _portrait;
	Sprite* _playerinfo;
	Sprite* _playerinfobutton;
	Sprite* _uiimage;
	Sprite* _hp;
	Sprite* _mana;
	Sprite* _skill1;
	Sprite* _skill2;
	Sprite* _skill3;
	Sprite* _minimapback;
	Sprite* _missionboard;
	Sprite* _potion;
	Sprite* _potionn;
	Sprite* _miniicon[32];
	Sprite* _miniplayer;

	Sprite* _skill1cool;
	Sprite* _skill2cool;
	Sprite* _skill3cool;

	Sprite* _hit;
	Sprite* _heal;
	Sprite* _avoid;

	Label* _mission;
	Label* _time;

	void initUI(Sprite* parent);

	void OpenEnemyInfo(std::wstring name);

	void CloseEnmeyInfo();

	void OpenMissionBoard();

	void CloseMissionBoard();

	void OpenPlayerInfo();

	void ClosePlayerInfo();

	void update();

};