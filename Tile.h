#pragma once

#include "Type.h"
#include <vector>
#include "GameMng.h"
#include <fstream>
#include "Sprite.h"

class Tile
{
public:
	static Tile* _tinstance;
	static Tile* getInstance()
	{
		if (!_tinstance)
			_tinstance = new Tile();
		return _tinstance;
	}

	Vec2 _size;
	std::vector<std::vector<char>> _map;

	void initMap(D3DXIMAGE_INFO in, Sprite* pa);

	//anchor is 0.5, 1
	Vec2 getPosByTile(Vec2 pos, D3DXIMAGE_INFO i);

	Vec2 getTileByPos(Vec2 tile, D3DXIMAGE_INFO i);

};