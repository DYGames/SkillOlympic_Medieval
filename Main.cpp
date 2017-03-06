#include "DXUT.h"
#include "Main.h"
#include "Stage.h"
#include "GameMng.h"

void Main::init()
{
	_game = new Sprite();
	_game->_active = true;
	this->addChild(_game);

	_ui = new Sprite();
	_ui->_active = true;
	this->addChild(_ui);
	_ui->_position = Vec2(0, -720);

	_buycount = 0;

	_mainb = new Sprite(_game, L"mainb.png", Vec2(640, 360));
	_mainb->_name = L"main";
	_mainb->_depth = 2;

	_mainstart = new Sprite(_game, L"mainstart.png", Vec2(640, 600));
	_mainstart->_tag = 'b';
	_mainstart->_name = L"main";
	_mainstart->_depth = 2;

	_stageb = new Sprite();
	_stageb->initWithFile(L"stageselect/1.png");
	_stageb->ani.initAnimation(_stageb, 0.1f, true);
	_stageb->ani.addClips(L"stageselect/2.png");
	_stageb->ani.addClips(L"stageselect/3.png");
	_stageb->_position = Vec2(640, 360);
	_ui->addChild(_stageb);

	_s1b = new Sprite();
	_s1b->initWithFile(L"stageselect/tree1.png");
	_s1b->_position = Vec2(390, 230);
	_ui->addChild(_s1b);

	_s2b = new Sprite();
	_s2b->initWithFile(L"stageselect/village1.png");
	_s2b->_position = Vec2(660, 540);
	_ui->addChild(_s2b);

	_s3b = new Sprite();
	_s3b->initWithFile(L"stageselect/castle.png");
	_s3b->_position = Vec2(990, 280);
	_ui->addChild(_s3b);

	_s1 = new Sprite();
	_s1->initWithFile(L"stageselect/s1.png");
	_s1->_position = Vec2(380, 280);
	_ui->addChild(_s1);

	_s2 = new Sprite();
	_s2->initWithFile(L"stageselect/s2.png");
	_s2->_position = Vec2(410, 480);
	_ui->addChild(_s2);

	_s3 = new Sprite();
	_s3->initWithFile(L"stageselect/s3.png");
	_s3->_position = Vec2(750, 180);
	_ui->addChild(_s3);

	_s4 = new Sprite();
	_s4->initWithFile(L"stageselect/s4.png");
	_s4->_position = Vec2(980, 400);
	_ui->addChild(_s4);

	_next = new Sprite();
	_next->initWithFile(L"stageselect/quitbtn.png");
	_next->_position = Vec2(1280 - (_next->_texture->_info.Width / 2), 720 - _next->_texture->_info.Height / 2);
	_ui->addChild(_next);

	_shop = new Sprite();
	_shop->initWithFile(L"stageselect/shop1.png");
	_shop->_position = Vec2(140, 550);
	_ui->addChild(_shop);

	_black = new Sprite();
	_black->initWithFile(L"black.png");
	_black->_position = Vec2(640, 360);
	_black->_color.a = 0.5f;
	_black->_visible = false;
	_ui->addChild(_black);


	_black->_depth = 4;
	_stageb->_depth = 1;
	_s1b->_depth = 2;
	_s2b->_depth = 2;
	_s3b->_depth = 2;
	_s1->_depth = 3;
	_s2->_depth = 3;
	_s3->_depth = 3;
	_s4->_depth = 3;
	_next->_depth = 3;
	_shop->_depth = 3;

	_load = new Sprite();
	_load->initWithFile(L"load.png");
	_load->_position = Vec2(640, 360);
	_load->_visible = false;
	_load->_depth = 31321;
	_ui->addChild(_load);

	_shopback = new Sprite();
	_shopback->initWithFile(L"shopback.png");
	_shopback->_position = Vec2(640, 720 + 360);
	_shopback->_visible = false;
	_shopback->_tag = 's';
	_ui->addChild(_shopback);

	_owner = new Sprite();
	_owner->initWithFile(L"shopowner.png");
	_owner->_position = Vec2(240, 720 + 240);
	_owner->_visible = false;
	_owner->_tag = 's';
	_ui->addChild(_owner);

	_potion = new Sprite();
	_potion->initWithFile(L"shoppotion.png");
	_potion->_position = Vec2(575, 720 + 225);
	_potion->_visible = false;
	_potion->_tag = 's';
	_ui->addChild(_potion);

	_mana = new Sprite();
	_mana->initWithFile(L"shopmana.png");
	_mana->_position = Vec2(575 + 150, 720 + 225);
	_mana->_visible = false;
	_mana->_tag = 's';
	_ui->addChild(_mana);

	_dmg = new Sprite();
	_dmg->initWithFile(L"shopdmg.png");
	_dmg->_position = Vec2(575 + 300, 720 + 225);
	_dmg->_visible = false;
	_dmg->_tag = 's';
	_ui->addChild(_dmg);

	_hlth = new Sprite();
	_hlth->initWithFile(L"shophlth.png");
	_hlth->_position = Vec2(575 + 450, 720 + 225);
	_hlth->_visible = false;
	_hlth->_tag = 's';
	_ui->addChild(_hlth);

	_up = new Sprite();
	_up->initWithFile(L"up.png");
	_up->_position = Vec2(1200, 720 + 80);
	_up->_visible = false;
	_up->_tag = 's';
	_ui->addChild(_up);

	_pop = new Sprite();
	_pop->initWithFile(L"shoppopup.png");
	_pop->_position = Vec2(640, 720 + 560);
	_pop->_visible = false;
	_pop->_tag = 's';
	_ui->addChild(_pop);

	_buy = new Sprite();
	_buy->initWithFile(L"buy.png");
	_buy->_position = Vec2(740, 720 + 640);
	_buy->_visible = false;
	_buy->_depth = 1;
	_buy->_tag = 's';
	_ui->addChild(_buy);

	_cancle = new Sprite();
	_cancle->initWithFile(L"cancle.png");
	_cancle->_position = Vec2(610, 720 + 640);
	_cancle->_visible = false;
	_cancle->_tag = 's';
	_ui->addChild(_cancle);

	_coin = new Sprite();
	_coin->initWithFile(L"coin.png");
	_coin->_position = Vec2(800, 720 + 120);
	_coin->_visible = false;
	_coin->_tag = 's';
	_coin->_depth = 2143;
	_ui->addChild(_coin);

	_money = new Label();
	_money->initFont(L"", 20);
	_money->_position = Vec2(850, 110);
	_money->_depth = 99999;
	_money->_visible = false;
	_money->_color = D3DXCOLOR(0, 0, 0, 1);
	_money->_tag = 's';
	_ui->addChild(_money);

	_lock2 = new Sprite();
	_lock2->initWithFile(L"lock.png");
	_lock2->_visible = !GameMng::getInstance()->_open2;
	_lock2->_position = Vec2(_s2->_position);
	_lock2->_depth = 1342;
	_ui->addChild(_lock2);
	_lock3 = new Sprite();
	_lock3->initWithFile(L"lock.png");
	_lock3->_visible = !GameMng::getInstance()->_open3;
	_lock3->_position = Vec2(_s3->_position);
	_lock3->_depth = 1342;
	_ui->addChild(_lock3);
	_lock4 = new Sprite();
	_lock4->initWithFile(L"lock.png");
	_lock4->_visible = !GameMng::getInstance()->_open4;
	_lock4->_position = Vec2(_s4->_position);
	_lock4->_depth = 1342;
	_ui->addChild(_lock4);
}

void Main::update()
{
	Node::update();

	WCHAR moneystr[256];
	swprintf(moneystr, L"%d", (int)GameMng::getInstance()->_money);

	_money->_str = moneystr;

	if (DXUTIsKeyDown(VK_LEFT))
		_money->_position.x -= 10;
	else if (DXUTIsKeyDown(VK_RIGHT))
		_money->_position.x += 10;
	else if (DXUTIsKeyDown(VK_UP))
		_money->_position.y -= 10;
	else if (DXUTIsKeyDown(VK_DOWN))
		_money->_position.y += 10;


	if (_mainstart->_rect.containsPoint(Input::mouseLocation()))
		_mainstart->ScaleTo(_mainstart->_scale.x, 1.4f, 1);
	else
		_mainstart->ScaleTo(_mainstart->_scale.x, 1, 1);

	if (_s1->_rect.containsPoint(Input::mouseLocation()))
	{
		_black->_visible = true;
		_s1->ScaleTo(_s1->_scale.x, 1.4f, 1);
		_s1->_depth = 5;
		_s1b->_depth = 5;
	}
	else if (_s2->_rect.containsPoint(Input::mouseLocation()) && GameMng::getInstance()->_open2)
	{
		_black->_visible = true;
		_s2->ScaleTo(_s2->_scale.x, 1.4f, 1);
		_s2->_depth = 5;
		_s2b->_depth = 5;
	}
	else if (_s3->_rect.containsPoint(Input::mouseLocation()) && GameMng::getInstance()->_open3)
	{
		_black->_visible = true;
		_s3->ScaleTo(_s3->_scale.x, 1.4f, 1);
		_s3->_depth = 5;
		_s3b->_depth = 5;
	}
	else if (_s4->_rect.containsPoint(Input::mouseLocation()) && GameMng::getInstance()->_open4)
	{
		_black->_visible = true;
		_s4->ScaleTo(_s4->_scale.x, 1.4f, 1);
		_s4->_depth = 5;
		_s3b->_depth = 5;
	}
	else if (_next->_rect.containsPoint(Input::mouseLocation()))
	{
		_black->_visible = true;
		_next->ScaleTo(_next->_scale.x, 1.4f, 1);
		_next->_depth = 5;
	}
	else if (_shop->_rect.containsPoint(Input::mouseLocation()))
	{
		_black->_visible = true;
		_shop->ScaleTo(_shop->_scale.x, 1.4f, 1);
		_shop->_depth = 5;
	}
	else
	{
		_black->_visible = false;
		_black->_depth = 4;
		_stageb->_depth = 1;
		_s1b->_depth = 2;
		_s2b->_depth = 2;
		_s3b->_depth = 2;
		_s1->_depth = 3;
		_s2->_depth = 3;
		_s3->_depth = 3;
		_s4->_depth = 3;
		_next->_depth = 3;
		_shop->_depth = 3;
		_s1->ScaleTo(_s1->_scale.x, 1.f, 1);
		_s2->ScaleTo(_s2->_scale.x, 1.f, 1);
		_s3->ScaleTo(_s3->_scale.x, 1.f, 1);
		_s4->ScaleTo(_s4->_scale.x, 1.f, 1);
		_next->ScaleTo(_next->_scale.x, 1.f, 1);
		_shop->ScaleTo(_shop->_scale.x, 1.f, 1);
	}

	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!_touch)
		{
			_touch = true;

			if (_mainb->_visible)
			{
				if (_mainstart->_rect.containsPoint(Input::mouseLocation()))
				{
					_ui->MoveTo(Vec2(), 10);
					_ui->_moveto = [=](){
						_mainb->_visible = false;
						_mainstart->_visible = false;
						_ui->_moveto = nullptr;
					};
				}
			}
			else
			{
				if (_ui->_position == Vec2())
				{
					if (_s1->_rect.containsPoint(Input::mouseLocation()))
					{
						_load->_visible = true;
						GameMng::getInstance()->_stage = 1;
						_game->Delay([=](){Load(); Director::getInstance()->replaceScene(new Stage()); }, 0.2f);

					}
					if (_s2->_rect.containsPoint(Input::mouseLocation()) && GameMng::getInstance()->_open2)
					{
						_load->_visible = true;
						GameMng::getInstance()->_stage = 2;
						_game->Delay([=](){Load(); Director::getInstance()->replaceScene(new Stage()); }, 0.2f);

					}
					if (_s3->_rect.containsPoint(Input::mouseLocation()) && GameMng::getInstance()->_open3)
					{
						_load->_visible = true;
						GameMng::getInstance()->_stage = 3;
						_game->Delay([=](){Load(); Director::getInstance()->replaceScene(new Stage()); }, 0.2f);

					}
					if (_s4->_rect.containsPoint(Input::mouseLocation()) && GameMng::getInstance()->_open4)
					{
						_load->_visible = true;
						GameMng::getInstance()->_stage = 4;
						_game->Delay([=](){Load(); Director::getInstance()->replaceScene(new Stage()); }, 0.2f);

					}
					if (_next->_rect.containsPoint(Input::mouseLocation()))
					{
						_ui->MoveTo(Vec2(0, -720), 20);
						_mainb->_visible = true;
						_mainstart->_visible = true;
					}
					if (_shop->_rect.containsPoint(Input::mouseLocation()))
					{
						_ui->MoveTo(Vec2(0, -720), 20);
						for (auto it : _ui->_children)
							if (it->_tag == 's')
								it->_visible = true;
						_pop->_visible = false;
						_buy->_visible = false;
						_cancle->_visible = false;
					}
				}
				if (_up->_rect.containsPoint(Input::mouseLocation() - _ui->_position))
				{
					_ui->MoveTo(Vec2(0, 0), 20);
					_ui->_moveto = [=](){
						for (auto it : _ui->_children)
							if (it->_tag == 's')
								it->_visible = false;
						_ui->_moveto = nullptr;
					};
				}

				if (_potion->_rect.containsPoint(Input::mouseLocation() - _ui->_position))
				{
					_buycount = 1;
					_pop->_visible = true;
					_buy->_visible = true;
					_cancle->_visible = true;
					_pop->ScaleTo(0, 1, 1);
				}
				if (_mana->_rect.containsPoint(Input::mouseLocation() - _ui->_position))
				{
					_buycount = 2;
					_pop->_visible = true;
					_buy->_visible = true;
					_cancle->_visible = true;
					_pop->ScaleTo(0, 1, 1);
				}
				if (_dmg->_rect.containsPoint(Input::mouseLocation() - _ui->_position))
				{
					_buycount = 3;
					_pop->_visible = true;
					_buy->_visible = true;
					_cancle->_visible = true;
					_pop->ScaleTo(0, 1, 1);
				}
				if (_hlth->_rect.containsPoint(Input::mouseLocation() - _ui->_position))
				{
					_buycount = 4;
					_pop->_visible = true;
					_buy->_visible = true;
					_cancle->_visible = true;
					_pop->ScaleTo(0, 1, 1);
				}

				if (_buy->_rect.containsPoint(Input::mouseLocation() - _ui->_position) && _buy->_visible)
				{
					switch (_buycount)
					{
						case 1:
							if (GameMng::getInstance()->_money > 20)
								GameMng::getInstance()->_potion++, GameMng::getInstance()->_money -= 20, Buy(true);
							else
								Buy(false);
							break;
						case 2:
							if (GameMng::getInstance()->_money > 10)
								GameMng::getInstance()->_mana++, GameMng::getInstance()->_money -= 10, Buy(true);
							else
								Buy(false);
							break;
						case 3:
							if (GameMng::getInstance()->_money > 50 && GameMng::getInstance()->_atkdmg < 5)
								GameMng::getInstance()->_atkdmg++, GameMng::getInstance()->_money -= 50, Buy(true);
							else
								Buy(false);
							break;
						case 4:
							if (GameMng::getInstance()->_money > 50 && GameMng::getInstance()->_maxhp < 100)
								GameMng::getInstance()->_maxhp += 25, GameMng::getInstance()->_money -= 50, Buy(true);
							else
								Buy(false);
							break;
					}

					_buycount = 0;
					_buy->_visible = false;
					_cancle->_visible = false;
					_pop->ScaleTo(1, 0, 1);
					_pop->_scaleto = [=](){_pop->_visible = false; _pop->_scaleto = nullptr; };
				}
				if (_cancle->_rect.containsPoint(Input::mouseLocation() - _ui->_position) && _cancle->_visible)
				{
					_buycount = 0;
					_buy->_visible = false;
					_cancle->_visible = false;
					_pop->ScaleTo(1, 0, 1);
					_pop->_scaleto = [=](){_pop->_visible = false; _pop->_scaleto = nullptr; };
				}
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

}

void Main::Buy(bool suc)
{
	if (suc)
	{
		Sprite* b = new Sprite();
		b->initWithFile(L"buysuc.png");
		b->_position = Vec2(1280 + 640, 720 + 320);
		_ui->addChild(b);
		b->MoveTo(b->_position + Vec2(-1280, 0), 2, true);
		b->_moveto = [=](){

			b->Delay([=](){
				b->MoveTo(b->_position + Vec2(-1280, 0), 2, true);
				b->_moveto = [=](){
					removeChild(b); };
			}, 1);
		};
	}
	else
	{
		Sprite* b = new Sprite();
		b->initWithFile(L"buyfail.png");
		b->_position = Vec2(1280 + 640, 720 + 320);
		_ui->addChild(b);
		b->MoveTo(b->_position + Vec2(-1280, 0), 2, true);
		b->_moveto = [=](){

			b->Delay([=](){
				b->MoveTo(b->_position + Vec2(-1280, 0), 2, true);
				b->_moveto = [=](){
					removeChild(b); };
			}, 1);
		};
	}
}

void Main::Load()
{
	WCHAR tmpstr[256];
	for (int i = 0; i < 8; i++)
	{
		swprintf(tmpstr, L"player/idle/left/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/idle/right/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/idle/top/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/idle/bottom/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/walk/left/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/walk/right/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/walk/top/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/walk/bottom/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/run/left/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/run/right/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/run/top/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/run/bottom/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/die/bottom/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/atk/left/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/atk/right/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/atk/top/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
		swprintf(tmpstr, L"player/atk/bottom/%d.png", i);
		TextureMng::getInstance()->getTexture(tmpstr);
	}

}

void Main::exit()
{
	for (auto it : _children)
		removeChild(it);
}