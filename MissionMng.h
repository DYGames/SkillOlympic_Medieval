#pragma once

#include "DXUT.h"
#include "Type.h"
#include "Sprite.h"
#include <map>
#include "GameMng.h"

typedef struct tagMission
{
	int _slimecount;
	int _bslimecount;
	int _skullcount;
	int _bronzecount;
	int _silvercount;
	int _goldcount;
	int _balecount;
	int _mamoncount;
	float _time;
}Mission;

class Player;
class Enemy;

class MissionMng
{
public:
	static MissionMng* _minstance;
	static MissionMng* getInstance()
	{
		if (!_minstance)
			_minstance = new MissionMng();
		return _minstance;
	}

	Node* _parent;
	Player* _player;

	std::map<int, Mission> _missions;
	std::map<int, Mission> _maxmissions;
	std::map<int, Mission> _spnmissions;

	float _starttime;
	float _chktime;
	float _prevtime;

	void initMission(Node* parent);

	bool getMissionClear();

	bool getMissionFail();

	void CallPerSec();

	Enemy* Spawn(std::wstring name, Vec2 pos = Vec2(-1, -1));

	void update();

	void ActiveMamon();
};