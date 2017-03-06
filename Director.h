#pragma once

#include "DXUT.h"
#include "Node.h"
#include "Type.h"

class Scene : public Node
{
public:

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;
};

class Director
{
public:
	Scene* _next;
	Scene* _cur;

	static LPD3DXSPRITE _sprite;

	static Director* _dinstance;
	static Director* getInstance()
	{
		if (!_dinstance)
			_dinstance = new Director();
		return _dinstance;
	}

	void replaceScene(Scene* s)
	{
		if (!_cur)
		{
			_cur = s;
			_cur->init();
		}
		else
			_next = s;
	}

	void update()
	{
		if (!_cur)
			return;

		if (_next)
		{
			_cur->exit();
			_cur->removeChildAll();
			_cur->deleteChildAll();
			_cur = _next;
			_cur->init();
			_next = NULL;
		}

		_cur->update();
		_cur->draw();
		_cur->addChildAll();
		_cur->removeChildAll();
		_cur->deleteChildAll();
	}
	
	void Release()
	{
		_cur->exit();
		_cur->removeChildAll();
		_cur->deleteChildAll();
		SAFE_DELETE(_cur);
	}

};