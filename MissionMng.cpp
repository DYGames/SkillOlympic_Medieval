#include "DXUT.h"
#include "MissionMng.h"
#include "Player.h"
#include "Tile.h"
#include "Enemy.h"

MissionMng* MissionMng::_minstance = NULL;

void MissionMng::initMission(Node* parent)
{
	_parent = parent;

	_starttime = 0;
	_chktime = 0;
	_prevtime = 0;

	_missions[1] = { 10, 3, -1, -1, -1, -1, -1, -1, 120 };
	_maxmissions[1] = { 10, 3, -1, -1, -1, -1, -1, -1, 120 };
	_spnmissions[1] = { 0, 0, -1, -1, -1, -1, -1, -1, 120 };
	_missions[2] = { 10, 3, 3, -1, -1, -1, -1, -1, 120 };
	_maxmissions[2] = { 10, 3, 3, -1, -1, -1, -1, -1, 120 };
	_spnmissions[2] = { 0, 0, 0, -1, -1, -1, -1, -1, 120 };
	_missions[3] = { -1, -1, 5, 3, 2, 1, 1, -1, 180 };
	_maxmissions[3] = { -1, -1, 5, 3, 2, 1, 1, -1, 180 };
	_spnmissions[3] = { -1, -1, 0, 0, 0, 0, 0, -1, 180 };
	_missions[4] = { 10, 5, 5, 3, 2, 1, -1, 1, 99999 };
	_maxmissions[4] = { 10, 5, 5, 3, 2, 1, -1, 1, 99999 };
	_spnmissions[4] = { 0, 0, 0, 0, 0, 0, -1, 1, 99999 };

	switch (GameMng::getInstance()->_stage)
	{
	case 1:
		Spawn(L"slime");
		Spawn(L"slime");
		Spawn(L"slime");
		Spawn(L"slime");
		Spawn(L"slime");

		_spnmissions[1]._slimecount += 5;
		break;
	case 2:
		Spawn(L"slime");
		Spawn(L"slime");
		Spawn(L"slime");
		Spawn(L"slime");
		Spawn(L"slime");

		_spnmissions[2]._slimecount += 5;
		break;
	case 3:
		Spawn(L"skull");
		Spawn(L"skull");
		Spawn(L"skull");
		Spawn(L"skull");
		Spawn(L"skull");

		_spnmissions[3]._skullcount += 5;
		break;
	case 4:
		Spawn(L"slime");
		Spawn(L"slime");
		Spawn(L"slime");
		Spawn(L"slime");
		Spawn(L"slime");

		Spawn(L"mamon", Vec2((Tile::getInstance()->_size.x / 2) - 3, 5));
		_spnmissions[4]._slimecount += 5;
		break;
	}
}

bool MissionMng::getMissionClear()
{
	int s = GameMng::getInstance()->_stage;
	if (_missions[s]._slimecount <= 0 && _missions[s]._bslimecount <= 0 && _missions[s]._skullcount <= 0 &&
		_missions[s]._bronzecount <= 0 && _missions[s]._silvercount <= 0 && _missions[s]._goldcount <= 0 &&
		_missions[s]._balecount <= 0 && _missions[s]._mamoncount <= 0 && _missions[s]._time > 0)
		return true;
	return false;
}

bool MissionMng::getMissionFail()
{
	if (_missions[GameMng::getInstance()->_stage]._time <= 0)
		return true;
	if (_player->_hp <= 0)
		return true;
	return false;
}

void MissionMng::CallPerSec()
{
	Vec2 ptile = Tile::getInstance()->getPosByTile(_player->_position, _player->_texture->_info);

	switch (GameMng::getInstance()->_stage)
	{
	case 1:
		if ((int)_prevtime == 5 && _spnmissions[1]._slimecount < _maxmissions[1]._slimecount)
			Spawn(L"slime"), _prevtime = 0, _chktime = 0, _spnmissions[1]._slimecount++;
		if ((int)_starttime == 30 && _spnmissions[1]._bslimecount == 0)
			Spawn(L"bigslime"), _spnmissions[1]._bslimecount++;
		if ((int)_starttime == 60 && _spnmissions[1]._bslimecount == 1)
			Spawn(L"bigslime"), _spnmissions[1]._bslimecount++;
		if ((int)_starttime == 90 && _spnmissions[1]._bslimecount == 2)
			Spawn(L"bigslime"), _spnmissions[1]._bslimecount++;
		break;
	case 2:
		if ((int)_prevtime == 5 && _spnmissions[2]._slimecount < _maxmissions[2]._slimecount)
			Spawn(L"slime"), _prevtime = 0, _chktime = 0, _spnmissions[2]._slimecount++;
		if ((int)_starttime == 30 && _spnmissions[2]._bslimecount == 0)
			Spawn(L"bigslime"), _spnmissions[2]._bslimecount++;
		if ((int)_starttime == 60 && _spnmissions[2]._bslimecount == 1)
			Spawn(L"bigslime"), _spnmissions[2]._bslimecount++;
		if ((int)_starttime == 90 && _spnmissions[2]._bslimecount == 2)
			Spawn(L"bigslime"), _spnmissions[2]._bslimecount++;
		if (_spnmissions[2]._bslimecount == _maxmissions[2]._bslimecount && _spnmissions[2]._skullcount == 0)
			Spawn(L"skull"), Spawn(L"skull"), Spawn(L"skull"), _spnmissions[2]._skullcount = 3;
		break;
	case 3:
		if (_spnmissions[3]._bronzecount == 0 && ((int)_starttime == 30 || _missions[3]._skullcount == 0))
		{
			_spnmissions[3]._bronzecount = 3;
			Spawn(L"bronze");
			Spawn(L"bronze");
			Spawn(L"bronze");
		}
		if (_spnmissions[3]._silvercount == 0 && ((int)_starttime == 60 || _missions[3]._bronzecount == 0))
		{
			_spnmissions[3]._silvercount = 2;
			Spawn(L"silver");
			Spawn(L"silver");
		}
		if (_spnmissions[3]._goldcount == 0 && ((int)_starttime == 90 || _missions[3]._silvercount == 0))
		{
			_spnmissions[3]._goldcount = 1;
			Spawn(L"gold");
		}
		if (_missions[3]._skullcount == 0 && _missions[3]._bronzecount == 0 && _missions[3]._silvercount == 0 && _missions[3]._goldcount == 0 && _spnmissions[3]._balecount == 0)
		{
			_spnmissions[3]._balecount = 1;
			Spawn(L"bale");
		}
		break;
	case 4:
		if ((int)_prevtime == 5 && _spnmissions[4]._slimecount < _maxmissions[4]._slimecount)
			Spawn(L"slime"), _prevtime = 0, _chktime = 0, _spnmissions[4]._slimecount++;
		if ((int)_starttime == 30 && _spnmissions[4]._bslimecount == 0)
			Spawn(L"bigslime"), _spnmissions[4]._bslimecount++;
		if ((int)_starttime == 60 && _spnmissions[4]._bslimecount == 1)
			Spawn(L"bigslime"), _spnmissions[4]._bslimecount++;
		if ((int)_starttime == 90 && _spnmissions[4]._bslimecount == 2)
			Spawn(L"bigslime"), _spnmissions[4]._bslimecount++;
		if ((int)_starttime == 120 && _spnmissions[4]._bslimecount == 3)
			Spawn(L"bigslime"), _spnmissions[4]._bslimecount++;
		if ((int)_starttime == 150 && _spnmissions[4]._bslimecount == 4)
			Spawn(L"bigslime"), _spnmissions[4]._bslimecount++;
		if ((int)_starttime == 60 && _spnmissions[4]._skullcount < _maxmissions[4]._skullcount)
			Spawn(L"skull", Vec2(ptile.x - 5, ptile.y)), Spawn(L"skull", Vec2(ptile.x + 5, ptile.y)), Spawn(L"skull", Vec2(ptile.x, ptile.y + 5)), Spawn(L"skull", Vec2(ptile.x, ptile.y - 5)), Spawn(L"skull", Vec2(ptile.x + 5, ptile.y + 4)), _spnmissions[4]._skullcount = 5;
		if (((int)_starttime == 90 && _spnmissions[4]._bronzecount < _maxmissions[4]._bronzecount) || _missions[4]._skullcount == 0)
			Spawn(L"bronze"), Spawn(L"bronze"), Spawn(L"bronze"), _spnmissions[4]._bronzecount = 3;
		if ((_missions[4]._bronzecount == 0 && _spnmissions[4]._silvercount == 0))
			Spawn(L"silver"), Spawn(L"silver"), _spnmissions[4]._silvercount = 2;
		if (_missions[4]._silvercount == 0 && _spnmissions[4]._goldcount == 0)
			Spawn(L"gold"), _spnmissions[4]._goldcount = 1;
		if (_missions[4]._slimecount <= 0 && _missions[4]._bslimecount <= 0 && _missions[4]._skullcount <= 0 &&
			_missions[4]._bronzecount <= 0 && _missions[4]._silvercount <= 0 && _missions[4]._goldcount <= 0)
		{
			ActiveMamon();
		}
		break;
	}
}

Enemy* MissionMng::Spawn(std::wstring name, Vec2 pos)//4 6 6 10 max - min max
{
	std::wstring enemystr = name;
	enemystr.append(L".png");

	int xx, yy;

	if (pos == Vec2(-1, -1))
	{
		xx = rand() % ((int)Tile::getInstance()->_size.x - 6 - 4) + 4;
		yy = rand() % ((int)Tile::getInstance()->_size.y - 6 - 4) + 4;
	}
	else
	{
		xx = pos.x;
		yy = pos.y;
	}

	Enemy* enemy = new Enemy(name, _player);
	enemy->_position = Tile::getInstance()->getPosByTile(Vec2(xx, yy), enemy->_texture->_info);
	enemy->_oripos = enemy->_position;
	_parent->addChild(enemy);

	return enemy;
}

void MissionMng::ActiveMamon()
{
	for (auto it : _parent->_children)
	{
		if (it->_name == L"mamon")
		{
			((Enemy*)it)->_mamonactive = true;
		}
	}
}

void MissionMng::update()
{
	_missions[GameMng::getInstance()->_stage]._time -= Time::dt;

	_starttime += Time::dt;
	_chktime += Time::dt;
	if ((int)_chktime != _prevtime)
	{
		_prevtime = _chktime;
		CallPerSec();
	}
}