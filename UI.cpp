#include "DXUT.h"
#include "UI.h"
#include "Stage.h"

UI* UI::_uinstance = NULL;

void UI::initUI(Sprite* parent)
{
	_parent = parent;

	_enemyinfo = new Sprite();
	_enemyinfo->initWithFile(L"slimeinfo.png");
	_enemyinfo->_position = Vec2(-(_enemyinfo->_texture->_info.Width / 2.f), _enemyinfo->_texture->_info.Height / 2.f);
	parent->addChild(_enemyinfo);

	_portrait = new Sprite();
	_portrait->initWithFile(L"portrait.png");
	_portrait->_position = Vec2(100, 600);
	parent->addChild(_portrait);

	_playerinfo = new Sprite();
	_playerinfo->initWithFile(L"playerinfo.png");
	_playerinfo->_position = Vec2(-(_playerinfo->_texture->_info.Width / 2.f), 420);
	parent->addChild(_playerinfo);

	_playerinfobutton = new Sprite();
	_playerinfobutton->initWithFile(L"playerinfobutton.png");
	_playerinfobutton->_position = Vec2(30, 515);
	parent->addChild(_playerinfobutton);

	_uiimage = new Sprite();
	_uiimage->initWithFile(L"uiimage.png");
	_uiimage->_position = Vec2(_uiimage->_texture->_info.Width / 2.f, 720 - (_uiimage->_texture->_info.Height / 2.f));
	parent->addChild(_uiimage);

	_hp = new Sprite();
	_hp->initWithFile(L"hp.png");
	_hp->_position = Vec2(150, 630);
	_hp->_anchor = Vec2(0, 0.5f);
	parent->addChild(_hp);

	_mana = new Sprite();
	_mana->initWithFile(L"mana0.png");
	_mana->_position = Vec2(380, 680);
	parent->addChild(_mana);

	_skill1 = new Sprite();
	_skill1->initWithFile(L"skill.png");
	_skill1->_position = Vec2(700, 670);
	parent->addChild(_skill1);

	_skill2 = new Sprite();
	_skill2->initWithFile(L"skill.png");
	_skill2->_position = Vec2(810, 670);
	parent->addChild(_skill2);

	_skill3 = new Sprite();
	_skill3->initWithFile(L"skill.png");
	_skill3->_position = Vec2(920, 670);
	parent->addChild(_skill3);

	_minimapback = new Sprite();
	_minimapback->initWithFile(L"minimapback.png");
	_minimapback->_position = Vec2(1280 - (_minimapback->_texture->_info.Width / 2.f), 720 - (_minimapback->_texture->_info.Height / 2));
	parent->addChild(_minimapback);

	_missionboard = new Sprite();
	_missionboard->initWithFile(L"missionboard.png");
	_missionboard->_position = Vec2(640, -(_missionboard->_texture->_info.Height / 2.f));
	parent->addChild(_missionboard);

	_mission = new Label();
	_mission->initFont(L"", 20);
	_mission->_color = { 0, 0, 0, 1 };
	_mission->_position = Vec2(_missionboard->_position);
	parent->addChild(_mission);

	_time = new Label();
	_time->initFont(L"", 40);
	_time->_color = { 0, 0, 0, 1 };
	_time->_position = Vec2(1110, 370);
	parent->addChild(_time);

	_potion = new Sprite();
	_potion->initWithFile(L"potion.png");
	_potion->_position = Vec2(250, 550);
	parent->addChild(_potion);

	_potionn = new Sprite();
	_potionn->initWithFile(L"0.png");
	_potionn->_position = Vec2(275, 575);
	_potionn->_depth = 1;
	parent->addChild(_potionn);

	_skill1cool = new Sprite();
	_skill1cool->initWithFile(L"skillcool.png");
	_skill1cool->_position = Vec2(_skill1->_position);
	_skill1cool->_depth = 234;
	parent->addChild(_skill1cool);

	_skill2cool = new Sprite();
	_skill2cool->initWithFile(L"skillcool.png");
	_skill2cool->_position = Vec2(_skill2->_position);
	_skill2cool->_depth = 234;
	parent->addChild(_skill2cool);

	_skill3cool = new Sprite();
	_skill3cool->initWithFile(L"skillcool.png");
	_skill3cool->_position = Vec2(_skill3->_position);
	_skill3cool->_depth = 234;
	parent->addChild(_skill3cool);

	_hit = new Sprite();
	_hit->initWithFile(L"hit.png");
	_hit->_position = Vec2(640, 360);
	_hit->_color.a = 0;
	parent->addChild(_hit);

	_heal = new Sprite();
	_heal->initWithFile(L"heal.png");
	_heal->_position = Vec2(640, 360);
	_heal->_color.a = 0;
	parent->addChild(_heal);

	_avoid = new Sprite();
	_avoid->initWithFile(L"avoid.png");
	_avoid->_position = Vec2(640, 360);
	_avoid->_color.a = 0;
	parent->addChild(_avoid);

	for (int i = 0; i < 32; i++)
	{
		_miniicon[i] = new Sprite();
		_miniicon[i]->initWithFile(L"slime.png");
		_miniicon[i]->_visible = false;
		_miniicon[i]->_scale = Vec2(0.3f, 0.3f);
		parent->addChild(_miniicon[i]);
	}
	_miniplayer = new Sprite();
	_miniplayer->initWithFile(L"player.png");
	_miniplayer->_visible = true;
	_miniplayer->_depth = 314;
	_miniplayer->_scale = Vec2(0.3f, 0.3f);
	parent->addChild(_miniplayer);

}

void UI::OpenEnemyInfo(std::wstring name)
{
	_enemyinfo->MoveTo(Vec2((_enemyinfo->_texture->_info.Width / 2.f), _enemyinfo->_texture->_info.Height / 2.f), 2, true);

	_enemyinfo->_texture = TextureMng::getInstance()->getTexture(name + L"info.png");
}

void UI::CloseEnmeyInfo()
{
	_enemyinfo->MoveTo(Vec2(-(_enemyinfo->_texture->_info.Width / 2.f), _enemyinfo->_texture->_info.Height / 2.f), 2, true);
}

void UI::OpenMissionBoard()
{
	_missionboard->MoveTo(Vec2(640, _missionboard->_texture->_info.Height / 2.f), 2, true);
}
void UI::CloseMissionBoard()
{
	_missionboard->MoveTo(Vec2(640, -(_missionboard->_texture->_info.Height / 2.f)), 2, true);
}

void UI::OpenPlayerInfo()
{
	_playerinfo->MoveTo(Vec2(100, 420), 2, true);
}

void UI::ClosePlayerInfo()
{
	_playerinfo->MoveTo(Vec2(-(_playerinfo->_texture->_info.Width / 2.f), 420), 2, true);
}

void UI::update()
{
	_skill1cool->_scale.y = (_skill1cool->_texture->_info.Height * (_player->_skill1cool / 3.f)) / 100.f;
	_skill2cool->_scale.y = (_skill2cool->_texture->_info.Height * (_player->_skill2cool / 5.f)) / 100.f;
	_skill3cool->_scale.y = (_skill3cool->_texture->_info.Height * (_player->_skill3cool / 1.f)) / 100.f;

	MissionMng::getInstance()->update();
	_mission->_position = Vec2(_missionboard->_rect.left, _missionboard->_rect.top);

	WCHAR tmpstr[256];
	if (GameMng::getInstance()->_mana > 10) GameMng::getInstance()->_mana = 10;
		swprintf(tmpstr, L"mana%d.png", GameMng::getInstance()->_mana);
	_mana->_texture = TextureMng::getInstance()->getTexture(tmpstr);

	_hp->_scale.x = 470.f * (_player->_hp / _player->_maxhp);

	swprintf(tmpstr, L"%d.png", GameMng::getInstance()->_potion);
	_potionn->_texture = TextureMng::getInstance()->getTexture(tmpstr);

	std::wstring missionstr;
	if (MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._slimecount > 0)
	{
		swprintf(tmpstr, L"남은 슬라임 : %d\n", MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._slimecount);
		missionstr.append(tmpstr);
	}
	if (MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._bslimecount > 0)
	{
		swprintf(tmpstr, L"남은 빅 슬라임 : %d\n", MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._bslimecount);
		missionstr.append(tmpstr);
	}
	if (MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._skullcount > 0)
	{
		swprintf(tmpstr, L"남은 해골 기사 : %d\n", MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._skullcount);
		missionstr.append(tmpstr);
	}
	if (MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._bronzecount > 0)
	{
		swprintf(tmpstr, L"남은 동 기사 : %d\n", MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._bronzecount);
		missionstr.append(tmpstr);
	}
	if (MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._silvercount > 0)
	{
		swprintf(tmpstr, L"남은 은 기사 : %d\n", MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._silvercount);
		missionstr.append(tmpstr);
	}
	if (MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._goldcount > 0)
	{
		swprintf(tmpstr, L"남은 금 기사 : %d\n", MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._goldcount);
		missionstr.append(tmpstr);
	}
	if (MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._balecount > 0)
	{
		swprintf(tmpstr, L"바알 처치\n", MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._balecount);
		missionstr.append(tmpstr);
	}
	if (MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._mamoncount > 0)
	{
		swprintf(tmpstr, L"마몬 처치\n", MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._mamoncount);
		missionstr.append(tmpstr);
	}
	if (MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._time < 999)
	{
		WCHAR tmpstr2[256];
		int t = MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._time;
		swprintf(tmpstr2, L"%d : %d", t / 60, t % 60);

		_time->_str = tmpstr2;
	}
	_mission->_str = missionstr;

	for (int i = 0; i < 32; i++)
		_miniicon[i]->_visible = false;
	int ecount = 0;
	for (auto it : ((Stage*)_parent->_parent)->_game->_children)
	{
		if (it->_tag == 'e')
		{
			_miniicon[ecount]->_visible = true;
			std::wstring str;
			str = it->_name;
			str.append(L".png");
			_miniicon[ecount]->_texture = TextureMng::getInstance()->getTexture(str);
			_miniicon[ecount]->_position = Vec2((float)_minimapback->_rect.left, (float)_minimapback->_rect.top) + (Vec2(it->_position.x * (_minimapback->_texture->_info.Width / 1900.f), it->_position.y * (_minimapback->_texture->_info.Height / 1050.f)));
			ecount++;
		}
	}

	_miniplayer->_position = Vec2((float)_minimapback->_rect.left, (float)_minimapback->_rect.top) + (Vec2(_player->_position.x * (_minimapback->_texture->_info.Width / 1900.f), _player->_position.y * (_minimapback->_texture->_info.Height / 1050.f)));

}