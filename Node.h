#pragma once

#include "DXUT.h"
#include "Type.h"
#include <vector>
#include <algorithm>

class Node
{
public:
	bool _active;
	bool _visible;
	float _rotation;
	float _depth;
	Vec2 _position;
	Vec2 _scale;
	Vec2 _anchor;

	Rect _rect;
	D3DXCOLOR _color;
	int _tag;
	std::wstring _name;

	Node* _parent;

	Node()
	{
		_depth = 0;
		_parent = NULL;
		_active = false;
		_visible = true;
		_rotation = 0;
		_position = Vec2();
		_scale = Vec2(1, 1);
		_anchor = Vec2(0.5f, 0.5f);
		_color = D3DXCOLOR(1, 1, 1, 1);
		_rect = Rect();
		_tag = 0;
		_name = L"";
		_children.clear();
		_willaddchild.clear();
		_removev.clear();

	}
	virtual ~Node(){}

	std::vector<Node*> _children;
	std::vector<Node*> _willaddchild;
	std::vector<Node*> _removev;

	void addChild(Node* c)
	{
		c->_parent = this;
		_willaddchild.push_back(c);
	}

	void removeChild(Node* c)
	{
		c->_active = false;
		for (auto it : c->_children)
			removeChild(it);
	}

	void addChildAll()
	{
		for (auto it : _willaddchild)
		{
			_children.push_back(it);
		}
		_willaddchild.clear();
		for (auto it : _children)
			it->addChildAll();
	}

	void removeChildAll()
	{
		for (auto it = _children.begin(); it != _children.end();)
		{
			(*it)->removeChildAll();
			if (!(*it)->_active)
			{
				_removev.push_back(*it);
				it = _children.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void deleteChildAll()
	{
		for (auto it : _removev)
		{
			if (it->_removev.size())
				it->deleteChildAll();
			SAFE_DELETE(it);
			printf("delete node\n");
		}
		_removev.clear();
	}

	virtual void update()
	{
		for (auto it : _children)
		{
			if (it->_active)
			{
				it->update();
			}
		}
	}

	virtual void draw()
	{
		std::sort(_children.begin(), _children.end(), [=](Node* a, Node* b){return a->_depth < b->_depth; });


		for (auto it : _children)
		{
			if (it->_active && it->_visible)
			{
				it->draw();
			}
		}
	}



	D3DXMATRIX getMatrix()
	{
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixTransformation2D(&mat, nullptr, NULL, &_scale, nullptr, _rotation, &_position);
		if (_parent)
			mat *= _parent->getMatrix();
		return mat;
	}

};

class Label : public Node
{
public:
	LPD3DXFONT _font;
	std::wstring _str;

	virtual ~Label()
	{
		SAFE_RELEASE(_font);
	}

	void initFont(std::wstring str, int pt)
	{
		_str = str;
		_active = true;
		D3DXCreateFont(DXUTGetD3D9Device(), pt, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0 | FF_DONTCARE, L"Consolas", &_font);
	}

	void draw() override
	{
		Rect rc = { _position.x, 0, _position.y, 0 };
		_font->DrawText(NULL, _str.c_str(), _str.size(), &rc, DT_NOCLIP, _color);
	}

};