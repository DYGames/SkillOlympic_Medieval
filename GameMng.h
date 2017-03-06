#pragma once

#include <map>

class GameMng
{
public:
	static GameMng* _ginstance;
	static GameMng* getInstance()
	{
		if (!_ginstance)
			_ginstance = new GameMng();
		return _ginstance;
	}

	GameMng()
	{

		reset();

	}

	void reset()
	{
		_stage = 1;
		_maxhp = 25;
		_atkdmg = 2;
		_mana = 0;
		_potion = 0;
		_money = 1000;
		_open2 = false;
		_open3 = false;
		_open4 = false;
		_rank.clear();
	}

	std::map<int, std::wstring> _rank;

	bool _open2;
	bool _open3;
	bool _open4;

	int _money;

	int _stage;

	int _maxhp;
	int _mana;
	int _atkdmg;
	int _potion;

};

