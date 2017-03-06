#include "DXUT.h"
#include "Stage.h"
#include "Player.h"
#include "Tile.h"
#include "Enemy.h"
#include "UI.h"
#include "Main.h"

void Stage::init()
{
	_game = new Sprite();
	_game->_active = true;
	this->addChild(_game);

	_game->ScaleTo(2, 1, 1.f / 2);

	_ui = new Sprite();
	_ui->_active = true;
	this->addChild(_ui);

	WCHAR str[256];
	swprintf(str, L"stage%d.png", GameMng::getInstance()->_stage);

	_initcount = 0;
	_initial[0] = 0;
	_initial[1] = 0;
	_initial[2] = 0;

	_stageb = new Sprite();
	_stageb->initWithFile(str);
	_stageb->_position = Vec2(_stageb->_texture->_info.Width / 2, _stageb->_texture->_info.Height / 2);
	_stageb->_tag = 'i';
	_game->addChild(_stageb);

	Tile::getInstance()->initMap(_stageb->_texture->_info, _game);

	_player = new Player();
	_player->initWithFile(L"player/idle/bottom/0.png");
	_player->ani.initAnimation(_player, 0.1f, true);
	_player->Animate();
	_player->_position = Tile::getInstance()->getPosByTile(Vec2(5, 5), _player->_texture->_info);
	_game->addChild(_player);

	_clear = new Sprite();
	_clear->initWithFile(L"clear.png");
	_clear->_position = Vec2(1280 + 640, 360);
	_clear->_depth = 12223;
	_ui->addChild(_clear);

	_next = new Sprite();
	_next->initWithFile(L"next.png");
	_next->_position = Vec2(1280 + 1280 - (_next->_texture->_info.Width / 2.f) - 35, 720 - (_next->_texture->_info.Height / 2.f) - 20);
	_next->_tag = 'b';
	_next->_depth = 12224;
	_ui->addChild(_next);

	_fail = new Sprite();
	_fail->initWithFile(L"fail.png");
	_fail->_position = Vec2(1280 + 640, 360);
	_fail->_depth = 12223;
	_ui->addChild(_fail);

	_retry = new Sprite();
	_retry->initWithFile(L"retry.png");
	_retry->_position = Vec2(1280 + 1280 - (_retry->_texture->_info.Width / 2.f) - 35, 720 - (_retry->_texture->_info.Height / 2.f) - 20);
	_retry->_tag = 'b';
	_retry->_depth = 12224;
	_ui->addChild(_retry);

	_grade = new Sprite();
	_grade->initWithFile(L"s.png");
	_grade->_color.a = 0;
	_grade->_position = Vec2(1000, 500);
	_grade->_depth = 22323;
	_ui->addChild(_grade);

	_cut = new Sprite();
	_cut->initWithFile(L"cut1.png");
	_cut->_position = Vec2(640, 360);
	_cut->_depth = 99999;
	_cut->_visible = false;
	_ui->addChild(_cut);

	_init1 = new Label();
	_init1->initFont(L"", 140);
	_init1->_position = Vec2(300, 450);
	_init1->_color = D3DXCOLOR(0, 0, 0, 1);
	_init1->_depth = 100000;
	_ui->addChild(_init1);
	_init2 = new Label();
	_init2->initFont(L"", 140);
	_init2->_position = Vec2(520, 450);
	_init2->_color = D3DXCOLOR(0, 0, 0, 1);
	_init2->_depth = 100000;
	_ui->addChild(_init2);
	_init3 = new Label();
	_init3->initFont(L"", 140);
	_init3->_position = Vec2(740, 450);
	_init3->_color = D3DXCOLOR(0, 0, 0, 1);
	_init3->_depth = 100000;
	_ui->addChild(_init3);

	UI::getInstance()->_player = _player;
	UI::getInstance()->initUI(_ui);

	MissionMng::getInstance()->_player = _player;
	MissionMng::getInstance()->initMission(_game);

}

void Stage::update()
{
	int score = (((int)MissionMng::getInstance()->_maxmissions[GameMng::getInstance()->_stage]._time - (int)MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._time) * 10) + (_player->_getMoney * 100);

	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!_touch)
		{
			_touch = true;

			if (_cut->_visible)
			{
				if (_initcount == 2)
				{
					Director::getInstance()->replaceScene(new Main());
					WCHAR str[256];
					swprintf(str, L"%c%c%c", _initial[0], _initial[1], _initial[2]);
					GameMng::getInstance()->_rank[score] = str;



				}
				if (_cut->_texture->_name == L"Resource/cut3.png")
					_cut->_texture = TextureMng::getInstance()->getTexture(L"cut4.png");
				if (_cut->_texture->_name == L"Resource/cut2.png")
					_cut->_texture = TextureMng::getInstance()->getTexture(L"cut3.png");
				if (_cut->_texture->_name == L"Resource/cut1.png")
					_cut->_texture = TextureMng::getInstance()->getTexture(L"cut2.png");
			}

			for (auto it : _game->_children)
			{
				if (it->_tag == 'e' && it->_rect.containsPoint(Input::mouseLocation() - _game->_position))
					UI::getInstance()->OpenEnemyInfo(it->_name), _enemyinfocount = 3;

			}

			if (_next->_rect.containsPoint(Input::mouseLocation()))
			{
				if (GameMng::getInstance()->_stage == 4)
					_cut->_visible = true;
				else
					Director::getInstance()->replaceScene(new Main());
			}
			else if (_retry->_rect.containsPoint(Input::mouseLocation()))
				Director::getInstance()->replaceScene(new Stage());

			if (UI::getInstance()->_playerinfobutton->_rect.containsPoint(Input::mouseLocation()))
			{
				if (UI::getInstance()->_playerinfo->_position.x == 100)
					UI::getInstance()->ClosePlayerInfo();
				else
					UI::getInstance()->OpenPlayerInfo();
			}


		}
	}
	else if (!(GetKeyState(VK_LBUTTON) & 0x8000))
	{
		if (_touch)
		{
			_touch = false;

		}
	}


	if (_initcount < 3 && _cut->_visible)
	{
		for (char i = 'A'; i < 'Z'; i++)
		{
			if (DXUTWasKeyPressed(i))
			{
				_initial[_initcount] = i;
				_initcount++;
				if (_initcount >= 2)
					_initcount = 2;
			}
		}
	}
	if (_initcount >= 0 && _cut->_visible)
	{
		if (DXUTWasKeyPressed(VK_BACK))
		{
			_initial[_initcount] = 0;
			_initcount--;
			if (_initcount <= 0)
				_initcount = 0;
		}
	}
	Node::update();

	_init1->_str = _initial[0];
	_init2->_str = _initial[1];
	_init3->_str = _initial[2];

	if (_cut->_visible)
		return;

	UI::getInstance()->update();

	_game->MoveTo(Vec2(640, 360) - _player->_position, 2, true);

	if ((MissionMng::getInstance()->getMissionClear() && !_end) || (_cheatclear && !_end))
	{
		_end = 1;

		_clear->MoveTo(Vec2(640, 360), 2, true);
		_next->MoveTo(Vec2(1280 - (_next->_texture->_info.Width / 2.f) - 35, 720 - (_next->_texture->_info.Height / 2.f) - 20), 2, true);
		_clear->_moveto = [=](){
			
			if (score > 1000)
				_grade->_texture = TextureMng::getInstance()->getTexture(L"s.png");
			else if (score > 500)
				_grade->_texture = TextureMng::getInstance()->getTexture(L"a.png");
			else
				_grade->_texture = TextureMng::getInstance()->getTexture(L"c.png");

			WCHAR str[256];
			swprintf(str, L"%d", ((int)MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._time));

			Label* remain = new Label();
			remain->initFont(str, 20);
			remain->_position = Vec2(870, 330);
			remain->_color = D3DXCOLOR(0, 0, 0, 1);
			remain->_depth = 83244;
			_ui->addChild(remain);
			swprintf(str, L"%d", _player->_getMoney);
			Label* getmoney = new Label();
			getmoney->initFont(str, 20);
			getmoney->_position = Vec2(870, 400);
			getmoney->_color = D3DXCOLOR(0, 0, 0, 1);
			getmoney->_depth = 83244;
			_ui->addChild(getmoney);

			swprintf(str, L"%d",score);
			Label* scorel = new Label();
			scorel->initFont(str, 20);
			scorel->_color = D3DXCOLOR(0, 0, 0, 1);
			scorel->_position = Vec2(870, 510);
			scorel->_depth = 83244;
			_ui->addChild(scorel);

			_grade->AlphaTo(0, 1, Time::dt);
		};
	}
	else if ((MissionMng::getInstance()->getMissionFail() && !_end) || (_cheatfail && !_end))
	{
		_end = 2;
		_fail->MoveTo(Vec2(640, 360), 2, true);
		_retry->MoveTo(Vec2(1280 - (_next->_texture->_info.Width / 2.f) - 35, 720 - (_next->_texture->_info.Height / 2.f) - 20), 2, true);
	}

	if (DXUTWasKeyPressed(VK_F4))
	{
		_cheatclear = true;
	}
	if (DXUTWasKeyPressed(VK_F9))
	{
		_cheatfail = true;
	}
	if (_opencount > 0)
		_opencount -= Time::dt;

	if (_opencount > 0)
		UI::getInstance()->OpenMissionBoard();
	else if (_opencount <= 0)
		UI::getInstance()->CloseMissionBoard();

	if (_enemyinfocount > 0)
		_enemyinfocount -= Time::dt;
	if (_enemyinfocount <= 0)
		UI::getInstance()->CloseEnmeyInfo();

	if (_game->_position.x > 0)
		_game->_position.x = 0;
	if (_game->_position.y > 0)
		_game->_position.y = 0;
	if (_game->_position.x < -620)
		_game->_position.x = -620;
	if (_game->_position.y < -310)
		_game->_position.y = -310;

	for (auto it : _game->_children)
	{
		if (it->_tag != 'i')
			it->_depth = it->_rect.bottom;
	}

	for (auto it : _game->_children)
	{
		if (it->_tag == 'e' || it->_tag == 'b')
		{
			if (it->_rect.containsPoint(Input::mouseLocation() - _game->_position))
			{
				if (it->_color.r > 0.8f)
					it->_color.r -= Time::dt;
			}
			else
			{
				if (it->_color.r < 1.f)
					it->_color.r += Time::dt;
			}
		}
	}

	

	if (Input::mouseLocation().y < 20)
		_opencount = 3;

}

void Stage::exit()
{
	for (auto it : _children)
		removeChild(it);
}