#include "DXUT.h"
#include "Enemy.h"
#include "Stage.h"
#include "Player.h"
#include "MissionMng.h"

#define sign(x) (x > 0 ? 1 : (x < 0 ? -1 : 0))

Enemy::Enemy(std::wstring name, Player* player)
{
	_player = player;
	_name = name;
	_tag = 'e';
	_mdelay = 0;
	_adelay = 0;
	_state = ENEMYSTATE::IDLE_BOTTOM;
	_dir = Vec2(0, -1);
	_skill1hiton = false;
	_skullspawncount = 0;
	_mamonactive = false;

	if (_name == L"slime")
	{
		initWithFile(L"slime/walk/0.png");
		_hp = _maxhp = 5;
		_attackdmg = 1;
		_maxmdelay = 1;
		_maxadelay = 2;
	}
	else if (_name == L"bigslime")
	{
		initWithFile(L"bigslime.png");
		_hp = _maxhp = 10;
		_attackdmg = 3;
		_maxmdelay = 0.9f;
		_maxadelay = 1.8f;
	}
	else if (_name == L"skull")
	{
		initWithFile(L"skull.png");
		_hp = _maxhp = 10;
		_attackdmg = 3;
		_maxmdelay = 0.8f;
		_maxadelay = 1.7f;
	}
	else if (_name == L"bronze")
	{
		initWithFile(L"bronze.png");
		_hp = _maxhp = 20;
		_attackdmg = 5;
		_maxmdelay = 0.75f;
		_maxadelay = 1.6f;
	}
	else if (_name == L"silver")
	{
		initWithFile(L"silver.png");
		_hp = _maxhp = 35;
		_attackdmg = 7;
		_maxmdelay = 0.7f;
		_maxadelay = 1.5f;
	}
	else if (_name == L"gold")
	{
		initWithFile(L"gold.png");
		_hp = _maxhp = 50;
		_attackdmg = 10;
		_maxmdelay = 0.65f;
		_maxadelay = 1.4f;
	}
	else if (_name == L"bale")
	{
		initWithFile(L"bale.png");
		_hp = _maxhp = 100;
		_attackdmg = 20;
		_maxmdelay = 0.6f;
		_maxadelay = 1.4f;
	}
	else if (_name == L"mamon")
	{
		initWithFile(L"mamon.png");
		_hp = _maxhp = 200;
		_attackdmg = 25;
		_maxmdelay = 0.55f;
		_maxadelay = 1.4f;
	}


	_hpback = new Sprite();
	_hpback->initWithFile(L"enemyhpback.png");
	_hpback->_scale.x = (float)_texture->_info.Width;
	_hpback->_depth = 90;
	_player->_parent->addChild(_hpback);
	_hpbar = new Sprite();
	_hpbar->initWithFile(L"enemyhpbar.png");
	_hpbar->_scale.x = (float)_texture->_info.Width;
	_hpbar->_depth = 91;
	_player->_parent->addChild(_hpbar);
	_aggro = new Sprite();
	_aggro->initWithFile(L"aggro.png");
	_aggro->_visible = false;
	_aggro->_anchor = Vec2(0, 0.5f);
	_aggro->_depth = 92;
	_player->_parent->addChild(_aggro);

}

void Enemy::Hitted(int dmg,Vec2 hitdir)
{
	_hp -= dmg;
	_dir = hitdir * -1;
	Vec2 np = _position - ((hitdir * -1) * 50);
	if (np.x > 50 && np.x < 1850 && np.y > 50 && np.y < 1000)
		MoveTo(np, 8, false);
	_hpbar->_scale.x = (float)_texture->_info.Width * ((float)_hp / (float)_maxhp);
	if (_hp <= 0)
	{
		Vec2 tp = Tile::getInstance()->getTileByPos(_position, _texture->_info);

		Sprite* coin = new Sprite();
		coin->initWithFile(L"coin.png");
		coin->_position = Tile::getInstance()->getPosByTile(tp, { 50, 50 });
		coin->MoveTo(coin->_position - Vec2(0, 50), 2);
		coin->_moveto = [=](){coin->_moveto = nullptr; coin->MoveTo(coin->_position + Vec2(0, 50), 2); };
		coin->_name = L"coin";
		coin->_tag = 't';
		_parent->addChild(coin);

		if (rand() % 2)
		{
			Sprite* potion = new Sprite();
			potion->initWithFile(L"ppotion.png");
			potion->_position = Tile::getInstance()->getPosByTile(Vec2(tp.x + 1, tp.y), { 50, 50 });
			potion->MoveTo(potion->_position - Vec2(0, 50), 2);
			potion->_moveto = [=](){potion->_moveto = nullptr; potion->MoveTo(potion->_position + Vec2(0, 50), 2); };
			potion->_name = L"potion";
			potion->_tag = 't';
			_parent->addChild(potion);
		}

		if (rand() % 2)
		{
			Sprite* mana = new Sprite();
			mana->initWithFile(L"mana.png");
			mana->_position = Tile::getInstance()->getPosByTile(Vec2(tp.x - 1, tp.y), { 50, 50 });
			mana->MoveTo(mana->_position - Vec2(0, 50), 2);
			mana->_moveto = [=](){mana->_moveto = nullptr; mana->MoveTo(mana->_position + Vec2(0, 50), 2); };
			mana->_name = L"mana";
			mana->_tag = 't';
			_parent->addChild(mana);
		}

		if (_name == L"slime")
			MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._slimecount--;
		else if (_name == L"bigslime")
			MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._bslimecount--;
		else if (_name == L"skull")
			MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._skullcount--;
		else if (_name == L"bronze")
			MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._bronzecount--;
		else if (_name == L"silver")
			MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._silvercount--;
		else if (_name == L"gold")
			MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._goldcount--;
		else if (_name == L"bale")
			MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._balecount--;
		else if (_name == L"mamon")
			MissionMng::getInstance()->_missions[GameMng::getInstance()->_stage]._mamoncount--;
		_state = ENEMYSTATE::DIE;
		Animate();
	}
}

void Enemy::Animate()
{
	switch (_state)
	{
	case ENEMYSTATE::IDLE_LEFT:
		break;
	case ENEMYSTATE::IDLE_RIGHT:
		break;
	case ENEMYSTATE::IDLE_TOP:
		break;
	case ENEMYSTATE::IDLE_BOTTOM:
		break;
	case ENEMYSTATE::MOVE_LEFT:
		break;
	case ENEMYSTATE::MOVE_RIGHT:
		break;
	case ENEMYSTATE::MOVE_TOP:
		break;
	case ENEMYSTATE::MOVE_BOTTOM:
		break;
	case ENEMYSTATE::ATK_LEFT:
		break;
	case ENEMYSTATE::ATK_RIGHT:
		break;
	case ENEMYSTATE::ATK_TOP:
		break;
	case ENEMYSTATE::ATK_BOTTOM:
		break;
	case ENEMYSTATE::DIE:
		removeChild(this);
		removeChild(_hpback);
		removeChild(_hpbar);
		removeChild(_aggro);
		if (_name == L"bigslime")
		{
			Vec2 tile = Tile::getInstance()->getTileByPos(_position, _texture->_info);

			MissionMng::getInstance()->Spawn(L"slime", Vec2(tile.x, tile.y));
			MissionMng::getInstance()->Spawn(L"slime", Vec2(tile.x + 1, tile.y));
			MissionMng::getInstance()->Spawn(L"slime", Vec2(tile.x + 1, tile.y - 1));
			MissionMng::getInstance()->Spawn(L"slime", Vec2(tile.x, tile.y - 1));

		}
		break;
	}
}

void Enemy::Attack()
{
	Vec2 etile = Tile::getInstance()->getTileByPos(_position, _texture->_info);
	Vec2 ptile = Tile::getInstance()->getTileByPos(_player->_position, _player->_texture->_info);

	float dmg = _attackdmg;

	if (_player->_defence)
	{
		if (_name == L"slime")
			dmg = 0;
		if (_name == L"bigslime")
			dmg = 1;
		if (_name == L"skull")
			dmg = 1;
		if (_name == L"bronze")
			dmg = 3;
		if (_name == L"silver")
			dmg = 5;
		if (_name == L"gold")
			dmg = 7;
		if (_name == L"bale")
			dmg = 10;
		if (_name == L"mamon")
			dmg = 15;

	}

	if (abs(ptile.x - etile.x) > 2)
		return;
	if (abs(ptile.y - etile.y) > 2)
		return;

	ptile.x = (int)ptile.x;
	ptile.y = (int)ptile.y;
	etile.x = (int)etile.x;
	etile.y = (int)etile.y;

	bool xcomp = false;
	for (int i = 0; i < _player->_texture->_info.Width / 50.f; i++)
	{
		if ((ptile.x == etile.x + i || ptile.x + 1 == etile.x + i))
			xcomp = true;
	}

	if (ptile.x >= etile.x && ptile.y == etile.y)
	{
		_player->Hitted(dmg);
		_state = ENEMYSTATE::ATK_LEFT;
	}
	else if (ptile.x < etile.x && ptile.y == etile.y)
	{
		_player->Hitted(dmg);
		_state = ENEMYSTATE::ATK_RIGHT;
	}
	else if (ptile.y >= etile.y && xcomp)
	{
		_player->Hitted(dmg);
		_state = ENEMYSTATE::ATK_TOP;
	}
	else if (ptile.y < etile.y && xcomp)
	{
		_player->Hitted(dmg);
		_state = ENEMYSTATE::ATK_BOTTOM;
	}
}

void Enemy::update()
{
	Sprite::update();

	if (_mamonactive)
	{
		if (!_brzspawn && ((float)_hp / _maxhp) < 0.9f)
		{
			MissionMng::getInstance()->Spawn(L"bronze");
			MissionMng::getInstance()->Spawn(L"bronze");
			_brzspawn = true;
		}
		else if (!_silspawn && ((float)_hp / _maxhp) < 0.6f)
		{
			MissionMng::getInstance()->Spawn(L"silver");
			MissionMng::getInstance()->Spawn(L"silver");
			_silspawn = true;
		}
		else if (!_gldspawn && ((float)_hp / _maxhp) < 0.3f)
		{
			MissionMng::getInstance()->Spawn(L"gold");
			MissionMng::getInstance()->Spawn(L"gold");
			_gldspawn = true;
		}

	}

	_hpback->_position = _position + Vec2(0, -(_texture->_info.Height / 2.f) - 10);
	_hpbar->_position = _position + Vec2(0, -(_texture->_info.Height / 2.f) - 10);
	_aggro->_position = _position + Vec2(0, -(_texture->_info.Height / 2.f) - 25);

	_skullspawncount += Time::dt;
	if (_skullspawncount >= 10.f && _name == L"bale")
	{
		_skullspawncount = 0;
		Vec2 ptile = Tile::getInstance()->getTileByPos(_position, _texture->_info);
		MissionMng::getInstance()->Spawn(L"skull", Vec2(ptile.x - 5, ptile.y));
		MissionMng::getInstance()->Spawn(L"skull", Vec2(ptile.x + 5, ptile.y));
		MissionMng::getInstance()->Spawn(L"skull", Vec2(ptile.x, ptile.y + 5));
		MissionMng::getInstance()->Spawn(L"skull", Vec2(ptile.x, ptile.y - 5));
		MissionMng::getInstance()->Spawn(L"skull", Vec2(ptile.x + 5, ptile.y + 4));
	}
	if (!_moves)
		_mdelay += Time::dt;

	_adelay += Time::dt;

	if (_adelay >= _maxadelay)
	{
		if (_name == L"bigslime")
		{
			if (_player->_position.distance(_position) > 100.f)
				RangeAttack();
			else
				Attack();
			_adelay = 0;
		}
		else
		{
			Attack();
			_adelay = 0;
		}
	}

	if (_mdelay >= _maxmdelay && !_moves)
	{
		if (((_player->_position.distance(_position) < 300.f) || (_name == L"skull" || _name == L"bronze" || _name == L"silver" || _name == L"gold")) && _name != L"bigslime")
		{
			_aggro->_visible = true;
			if (rand() % 2)
			{
				MoveTo(Vec2(_position.x, _position.y + (sign(_player->_position.y - _position.y) * 50.f)), 2), _mdelay = 0;
				_dir = Vec2(0, sign(_player->_position.y - _position.y));
			}
			else
			{
				MoveTo(Vec2(_position.x + (sign(_player->_position.x - _position.x) * 50.f), _position.y), 2), _mdelay = 0;
				_dir = Vec2(sign(_player->_position.x - _position.x), 0);
			}

			_mdelay = 0;
		}
		else
		{
			if (_name == L"mamon" && !_mamonactive)
				return;

			_aggro->_visible = false;
			Vec2 willpos;
			Vec2 willtile;
			switch (rand() % 4)
			{
			case 0:
				willpos = _position + Vec2(50, 0);
				break;
			case 1:
				willpos = _position + Vec2(-50, 0);
				break;
			case 2:
				willpos = _position + Vec2(0, -50);
				break;
			case 3:
				willpos = _position + Vec2(0, 50);
				break;
			}
			if (willpos.distance(_oripos) < 300)
			{
				MoveTo(willpos, 2);
				_mdelay = 0;
			}
		}
	}
}

void Enemy::RangeAttack()
{
	Vec2 etile = Tile::getInstance()->getTileByPos(_position, _texture->_info);
	Enemy* slime = MissionMng::getInstance()->Spawn(L"slime", etile);
	slime->MoveTo(_player->_position, 8, false);
}