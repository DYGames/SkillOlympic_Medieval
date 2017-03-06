#pragma once

#include "DXUT.h"
#include "Director.h"
#include "Node.h"
#include "Animation.h"
#include <functional>

class Texture
{
public:
	LPDIRECT3DTEXTURE9 _texture;
	D3DXIMAGE_INFO _info;
	std::wstring _name;
};

class TextureMng
{
public:
	static TextureMng* _tinstance;
	static TextureMng* getInstance()
	{
		if (!_tinstance)
			_tinstance = new TextureMng();
		return _tinstance;
	}

	std::vector<Texture*> _textures;

	Texture* getTexture(std::wstring path)
	{
		std::wstring realpath;
		realpath = L"Resource/" + path;

		Texture* t = new Texture();
		
		for (auto it : _textures)
		{
			if (it->_name == realpath)
				return it;
		}

		if (FAILED(
			D3DXCreateTextureFromFileEx(
			DXUTGetD3D9Device(),
			realpath.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			1,
			0,
			D3DFORMAT::D3DFMT_A8B8G8R8,
			D3DPOOL::D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			0,
			&t->_info,
			nullptr,
			&t->_texture
			)))
			return NULL;

		D3DXGetImageInfoFromFile(realpath.c_str(), &t->_info);

		t->_name = realpath;
		_textures.push_back(t);

		return t;
	}

	void Release()
	{
		for (auto it : _textures)
		{
			SAFE_RELEASE(it->_texture);
			SAFE_DELETE(it);
			printf("release texture");
		}
		_textures.clear();
	}

};

class Sprite : public Node
{
public:
	Sprite(){}
	Sprite(std::wstring s)
	{
		initWithFile(s);
	}
	Sprite(std::wstring s, Vec2 p)
	{
		initWithFile(s);
		_position = p;
	}
	Sprite(Node* r, std::wstring s, Vec2 p)
	{
		initWithFile(s);
		_position = p;
		r->addChild(this);
	}
	virtual ~Sprite(){}

	Animation ani;
	Texture* _texture = nullptr;

	Vec2 _movet = Vec2();
	float _moves = 0;
	bool _movel = false;
	Vec2 _normalized = Vec2();
	std::function<void()> _moveto;

	float _alphat = 0;
	float _alphas = 0;
	std::function<void()> _alphato;

	float _scalet = 0;
	float _scales = 0;
	std::function<void()> _scaleto;

	float _maxdelay = 0;
	std::function<void()> _delayf;

	void MoveTo(Vec2 t, float s, bool l = false)
	{
		_movet = t;
		_moves = s;
		_movel = l;
		D3DXVec2Normalize(&_normalized, &(_movet - _position));
	}

	void AlphaTo(float sl, float tl, float s)
	{
		_color.a = sl;
		_alphat = tl;
		_alphas = s;
	}

	void ScaleTo(float ss, float ts, float s)
	{
		_scale = Vec2(ss, ss);
		_scalet = ts;
		_scales = s;
	}

	void Delay(std::function<void()> d, float t)
	{
		_maxdelay = t;
		_delayf = d;
	}

	void initWithFile(std::wstring path)
	{
		_active = true;
		_texture = TextureMng::getInstance()->getTexture(path);
	}

	void update()
	{
		Node::update();

		if (_moves)
		{
			if (_movel)
			{
				D3DXVec2Lerp(&_position, &_position, &_movet, 0.1f * (_moves / 2.f));
			}
			else
			{
				_position += _normalized * _moves;
			}
			float dis = _position.distance(_movet);
			if (dis <= 2.f)
			{
				_moves = 0, _position = _movet;
				if (_moveto)
					_moveto();
			}
		}

		if (_alphas)
		{
			if (_color.a > _alphat)
				_color.a -= _alphas;
			else
				_color.a += _alphas;
			if (abs(_color.a - _alphat) <= 0.025f)
			{
				_color.a = _alphat, _alphas = 0;
				if (_alphato)
					_alphato();
			}
		}

		if (_scales)
		{
			D3DXVec2Lerp(&_scale, &_scale, &Vec2(_scalet, _scalet), 0.1f * (_scales));
			if (_position.distance(_movet) <= 0.025f)
			{
				_scales = 0, _scale = Vec2(_scalet, _scalet);
				if (_scaleto)
					_scaleto();
			}
		}

		if (_maxdelay)
		{
			_maxdelay -= Time::dt;
			if (_maxdelay <= 0)
			{
				_maxdelay = 0;
				_delayf();
			}
		}


		if (_texture)
		{
			_rect.left = _position.x - _texture->_info.Width / 2;
			_rect.right = _position.x + _texture->_info.Width / 2;
			_rect.top = _position.y - _texture->_info.Height / 2;
			_rect.bottom = _position.y + _texture->_info.Width / 2;
		}


	}

	void draw() override;

};