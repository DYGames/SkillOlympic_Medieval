#include "DXUT.h"
#include "Player.h"
#include "Stage.h"
#include "UI.h"

Player::Player()
{
	_mspeed = 6;
	_maxmdelay = 0.25f;
	_mdelay = 0;
	_state = PLAYERSTATE::IDLE_BOTTOM;
	_prevstate = PLAYERSTATE::IDLE_BOTTOM;
	_dir = Vec2(0, -1);
	_getMoney = 0;

	_hp = GameMng::getInstance()->_maxhp;
	_maxhp = GameMng::getInstance()->_maxhp;
	_attackdmg = GameMng::getInstance()->_atkdmg;
	_mana = GameMng::getInstance()->_mana;

	_skill1cool = 0; 
	_skill2cool = 0;
	_skill3cool = 0;
}

void Player::update()
{
	Sprite::update();

	if (_skill1cool > 0)
	{
		_skill1cool -= Time::dt;
		if (_skill1cool <= 0)
			_skill1cool = 0;
	}
	if (_skill2cool > 0)
	{
		_skill2cool -= Time::dt;
		if (_skill2cool <= 0)
			_skill2cool = 0;
	}
	if (_skill3cool > 0)
	{
		_skill3cool -= Time::dt;
		if (_skill3cool <= 0)
			_skill3cool = 0;
	}

	for (auto it : _parent->_children)
	{
		if (it->_position.y > _position.y && it->_rect.intersectRect(_rect) && it->_name == L"build")
		{
			((Sprite*)it)->AlphaTo(it->_color.a, 0.4f, Time::dt);
		}
		else if (it->_name == L"build" && it->_color.a < 1.f)
		{
			((Sprite*)it)->AlphaTo(it->_color.a, 1.f, Time::dt);
		}
	}

	if (!(_state == PLAYERSTATE::DFC_LEFT || _state == PLAYERSTATE::DFC_RIGHT || _state == PLAYERSTATE::DFC_TOP || _state == PLAYERSTATE::DFC_BOTTOM))
	{
		if (DXUTIsKeyDown('W'))
		{
			MoveDir(Vec2(0, -1));
			_state = PLAYERSTATE::MOVE_TOP;
		}
		else if (DXUTIsKeyDown('A'))
		{
			MoveDir(Vec2(-1, 0));
			_state = PLAYERSTATE::MOVE_LEFT;
		}
		else if (DXUTIsKeyDown('S'))
		{
			MoveDir(Vec2(0, 1));
			_state = PLAYERSTATE::MOVE_BOTTOM;
		}
		else if (DXUTIsKeyDown('D'))
		{
			MoveDir(Vec2(1, 0));
			_state = PLAYERSTATE::MOVE_RIGHT;
		}
	}
	if (DXUTIsKeyDown('E'))
	{
		_defence = true;
		if (_dir == Vec2(-1, 0))
			_state = PLAYERSTATE::DFC_LEFT;
		if (_dir == Vec2(1, 0))
			_state = PLAYERSTATE::DFC_RIGHT;
		if (_dir == Vec2(0, 1))
			_state = PLAYERSTATE::DFC_BOTTOM;
		if (_dir == Vec2(0, -1))
			_state = PLAYERSTATE::DFC_TOP;
	}
	else
		_defence = false;

	if (DXUTIsKeyDown('Z'))
	{
		for (auto it : _parent->_children)
		{
			if (it->_tag == 't' && it->_rect.intersectRect(_rect))
			{
				Sprite* item = new Sprite();
				item->_position = Vec2(it->_position + _parent->_position);
				if (it->_name == L"coin")
					item->initWithFile(L"coin.png"), item->MoveTo(Vec2(100, 640), 6), item->AlphaTo(1, 0, 1 / 240.f), item->_moveto = [=](){
					removeChild(item);
					_getMoney += 1;
					GameMng::getInstance()->_money += 1;
				};
				else if (it->_name == L"potion")
					item->initWithFile(L"ppotion.png"), item->MoveTo(Vec2(250, 550), 6), item->AlphaTo(1, 0, 1 / 240.f), item->_moveto = [=](){
					removeChild(item);
					GameMng::getInstance()->_potion += 1;
				};
				else if (it->_name == L"mana")
				{
					item->initWithFile(L"mana.png");
					item->MoveTo(Vec2(135 + (GameMng::getInstance()->_mana * 50), 680), 6), item->AlphaTo(1, 0, 1 / 240.f),
						item->_moveto = [=](){
						removeChild(item);
						GameMng::getInstance()->_mana += 1;
					};
				}
				((Stage*)_parent->_parent)->_ui->addChild(item);

				removeChild(it);

			}
		}
	}

	if (DXUTWasKeyPressed(VK_F1))
	{
		_god = true;
	}
	if (DXUTWasKeyPressed(VK_F2))
	{
		GameMng::getInstance()->_mana++;
	}
	if (DXUTWasKeyPressed(VK_F3))
	{
		for (auto it : _parent->_children)
		{
			if (it->_tag == 'e')
			{
				((Enemy*)it)->_state = Enemy::ENEMYSTATE::DIE;
			}
		}
	}

	if (DXUTWasKeyPressed(VK_SPACE))
	{
		for (auto it : _parent->_children)
		{
			Vec2 ptile = Tile::getInstance()->getTileByPos(_position, _texture->_info);
			Vec2 etile = Tile::getInstance()->getTileByPos(it->_position, ((Sprite*)it)->_texture->_info);

			ptile.x = (int)ptile.x;
			ptile.y = (int)ptile.y;
			etile.x = (int)etile.x;
			etile.y = (int)etile.y;

			if (it->_tag == 'e')
			{
				float tp;
				if (_dir.x == -1)
				{
					if (ptile.x >= etile.x && ptile.y == etile.y)
					{
						((Enemy*)it)->Hitted(_attackdmg, Vec2(-1, 0));
						_state = PLAYERSTATE::ATK_LEFT;
					}
				}
				else if (_dir.x == 1)
				{
					if (ptile.x < etile.x && ptile.y == etile.y)
					{
						((Enemy*)it)->Hitted(_attackdmg, Vec2(1, 0));
						_state = PLAYERSTATE::ATK_RIGHT;
					}
				}
				else if (_dir.y == -1)
				{
					if (ptile.y >= etile.y && (ptile.x == etile.x || ptile.x + 1 == etile.x))
					{
						((Enemy*)it)->Hitted(_attackdmg, Vec2(0, -1));
						_state = PLAYERSTATE::ATK_TOP;
					}
				}
				else if (_dir.y == 1)
				{
					if (ptile.y < etile.y && (ptile.x == etile.x || ptile.x + 1 == etile.x))
					{
						((Enemy*)it)->Hitted(_attackdmg, Vec2(0, 1));
						_state = PLAYERSTATE::ATK_BOTTOM;
					}
				}
			}
		}
	}

	if (DXUTWasKeyPressed('H'))
	{
		if (GameMng::getInstance()->_potion > 0)
		{
			UI::getInstance()->_heal->AlphaTo(0, 1, Time::dt);
			UI::getInstance()->_heal->_alphato = [=](){UI::getInstance()->_heal->AlphaTo(1, 0, Time::dt); UI::getInstance()->_heal->_alphato = nullptr; };

			GameMng::getInstance()->_potion--;
			_hp += 20;
			if (_hp > _maxhp)
				_hp = _maxhp;
		}
	}

	if (DXUTWasKeyPressed('1') && _skill1cool == 0 && GameMng::getInstance()->_mana > 3)
	{
		GameMng::getInstance()->_mana -= 2;
		UseSkill(1);
		_skill1cool = 3;
	}
	if (DXUTWasKeyPressed('2') && _skill2cool == 0 && GameMng::getInstance()->_mana > 5)
	{
		GameMng::getInstance()->_mana -= 3;
		UseSkill(2);
		_skill2cool = 5;
	}
	if (DXUTWasKeyPressed('3') && _skill3cool == 0 && GameMng::getInstance()->_mana > 1)
	{
		GameMng::getInstance()->_mana -= 1;
		UseSkill(3);
		_skill3cool = 1;
	}


	if (GetKeyState(VK_RBUTTON) & 0x8000)
	{
		if (!_rtouch)
		{
			_rtouch = true;

			for (auto it : _parent->_children)
			{
				if (it->_tag == 'e' && it->_rect.containsPoint(Input::mouseLocation() - _parent->_position))
				{
					Vec2 ptile = Tile::getInstance()->getTileByPos(_position, _texture->_info);
					Vec2 etile = Tile::getInstance()->getTileByPos(it->_position, ((Sprite*)it)->_texture->_info);

					if (abs(ptile.x - etile.x) > 2)
						break;
					if (abs(ptile.y - etile.y) > 2)
						break;

					ptile.x = (int)ptile.x;
					ptile.y = (int)ptile.y;
					etile.x = (int)etile.x;
					etile.y = (int)etile.y;

					bool xcomp = false;
					for (int i = 0; i < ((Sprite*)it)->_texture->_info.Width / 50.f; i++)
					{
						if ((ptile.x == etile.x + i || ptile.x + 1 == etile.x + i))
							xcomp = true;
					}

					if (ptile.x >= etile.x && ptile.y == etile.y)
					{
						((Enemy*)it)->Hitted(_attackdmg, Vec2(-1, 0));
						_state = PLAYERSTATE::ATK_LEFT;
					}
					else if (ptile.x < etile.x && ptile.y == etile.y)
					{
						((Enemy*)it)->Hitted(_attackdmg, Vec2(1, 0));
						_state = PLAYERSTATE::ATK_RIGHT;
					}
					else if (ptile.y >= etile.y && xcomp)
					{
						((Enemy*)it)->Hitted(_attackdmg, Vec2(0, -1));
						_state = PLAYERSTATE::ATK_TOP;
					}
					else if (ptile.y < etile.y && xcomp)
					{
						((Enemy*)it)->Hitted(_attackdmg, Vec2(0, 1));
						_state = PLAYERSTATE::ATK_BOTTOM;
					}
				}
			}

		}
	}
	else if (!(GetKeyState(VK_RBUTTON) & 0x8000))
	{
		if (_rtouch)
		{
			_rtouch = false;

		}
	}

	if (DXUTIsKeyDown(VK_MBUTTON))
		_mspeed = 8, _maxmdelay = 0.05f;
	else
		_mspeed = 6, _maxmdelay = 0.25f;

	if (!_moves)
		_mdelay += Time::dt;

	for (auto it : _parent->_children)
		if (it->_tag == 'e' && it->_rect.intersectRect(_rect))
			if (((Enemy*)it)->_skill1hiton)
				((Enemy*)it)->Hitted(20, _dir), ((Enemy*)it)->_skill1hiton = false;

	Animate();
}

void Player::UseSkill(int t)
{
	if (t == 1)
	{
		Vec2 pos = _parent->_position;
		//((Sprite*)_parent)->ScaleTo(1, 1.5f, 2);
		//((Sprite*)_parent)->_scaleto = [=](){
		MoveTo(_position + Vec2(_dir.x * 400, _dir.y * 400), 6, true);
		_skill1on = true;
		_state = PLAYERSTATE::DEFAULT;
		for (auto it : _parent->_children)
			if (it->_tag == 'e')
				((Enemy*)it)->_skill1hiton = true;

		_moveto = [=](){_skill1on = false; _state = PLAYERSTATE::IDLE_LEFT;
		for (auto it : _parent->_children)
			if (it->_tag == 'e')
				((Enemy*)it)->_skill1hiton = false;
		//	((Sprite*)_parent)->_scaleto = nullptr;
		//	((Sprite*)_parent)->ScaleTo(1.5f, 1, 2);
		//	};
		};
		return;
	}
	if (t == 2)
	{

		return;
	}
	if (t == 3)
	{
		_avoid = true;
		return;
	}

}

void Player::MoveDir(Vec2 dir)
{
	_dir = dir;

	if (!_moves && _mdelay > _maxmdelay)
	{
		Vec2 tile = Tile::getInstance()->getTileByPos(Vec2(_position.x + (dir.x * 50.f), _position.y + (dir.y * 50.f)), _texture->_info);
		if (tile.x <= 0 || tile.x >= Tile::getInstance()->_size.x - 1 || tile.y <= 1 || tile.y >= Tile::getInstance()->_size.y - 1)
			return;
		char ta = Tile::getInstance()->_map[(int)tile.y + 1][(int)tile.x + 1];
		char ta2 = Tile::getInstance()->_map[(int)tile.y + 1][(int)tile.x + 2];
		if (ta == '0' && ta2 == '0')
			MoveTo(Vec2(_position.x + (dir.x * 50.f), _position.y + (dir.y * 50.f)), _mspeed), _mdelay = 0;
	}
}

void Player::Hitted(int dmg)
{
	if (!(((Stage*)_parent->_parent)->_cut->_visible) && !_god)
	{
		if (_avoid)
		{
			UI::getInstance()->_avoid->AlphaTo(0, 1, Time::dt);
			UI::getInstance()->_avoid->_alphato = [=](){UI::getInstance()->_avoid->AlphaTo(1, 0, Time::dt); UI::getInstance()->_avoid->_alphato = nullptr; };
			_avoid = false;
		}
		else
		{
			UI::getInstance()->_hit->AlphaTo(0, 1, Time::dt);
			UI::getInstance()->_hit->_alphato = [=](){UI::getInstance()->_hit->AlphaTo(1, 0, Time::dt); UI::getInstance()->_hit->_alphato = nullptr; };

			_hp -= dmg;

			if (_hp <= 0)
			{
				_state = PLAYERSTATE::DIE;
			}
		}
	}
}

void Player::Animate()
{
	if (_prevstate == _state)
		return;
	ani.removeClipAll();
	ani._run = true;
	ani._loop = false;
	ani._erase = false;
	ani._endfunc = [=](){
		if (_dir == Vec2(-1, 0))
			_state = PLAYERSTATE::IDLE_LEFT;
		if (_dir == Vec2(1, 0))
			_state = PLAYERSTATE::IDLE_RIGHT;
		if (_dir == Vec2(0, 1))
			_state = PLAYERSTATE::IDLE_BOTTOM;
		if (_dir == Vec2(0, -1))
			_state = PLAYERSTATE::IDLE_TOP;
	};

	WCHAR tmpstr[256];

	_prevstate = _state;

	switch (_state)
	{
	case PLAYERSTATE::IDLE_LEFT:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/idle/left/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::IDLE_RIGHT:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/idle/right/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::IDLE_TOP:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/idle/top/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::IDLE_BOTTOM:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/idle/bottom/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::MOVE_LEFT:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/walk/left/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::MOVE_RIGHT:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/walk/right/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::MOVE_TOP:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/walk/top/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::MOVE_BOTTOM:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/walk/bottom/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::RUN_LEFT:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/run/left/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::RUN_RIGHT:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/run/right/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::RUN_TOP:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/run/top/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::RUN_BOTTOM:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/run/bottom/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::ATK_LEFT:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/atk/left/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::ATK_RIGHT:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/atk/right/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::ATK_TOP:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/atk/top/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::ATK_BOTTOM:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/atk/bottom/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	case PLAYERSTATE::DFC_LEFT:
		break;
	case PLAYERSTATE::DFC_RIGHT:
		break;
	case PLAYERSTATE::DFC_TOP:
		break;
	case PLAYERSTATE::DFC_BOTTOM:
		break;
	case PLAYERSTATE::TURN_LEFTTOTOP:
		break;
	case PLAYERSTATE::TURN_RIGHTTOTOP:
		break;
	case PLAYERSTATE::TURN_BOTTOMTOLEFT:
		break;
	case PLAYERSTATE::TURN_TOPTOLEFT:
		break;
	case PLAYERSTATE::TURN_LEFTTOBOTTOM:
		break;
	case PLAYERSTATE::TURN_RIGHTTOBOTTOM:
		break;
	case PLAYERSTATE::TURN_TOPTORIGHT:
		break;
	case PLAYERSTATE::TURN_BOTTOMTORIGHT:
		break;
	case PLAYERSTATE::DIE:
		for (int i = 0; i < 8; i++)
		{
			swprintf(tmpstr, L"player/die/bottom/%d.png", i);
			ani.addClips(tmpstr);
		}
		break;
	default:
		break;
	}
}