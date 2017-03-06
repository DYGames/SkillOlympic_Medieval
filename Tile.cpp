#include "DXUT.h"
#include "Tile.h"

Tile* Tile::_tinstance = NULL;

void Tile::initMap(D3DXIMAGE_INFO in, Sprite* pa)
{
	CHAR str[256];
	sprintf(str, "stage%d.txt", GameMng::getInstance()->_stage);

	std::fstream file(str);

	_map.resize(in.Height / 50.f);
	for (int j = 0; j < _map.size(); j++)
		_map.at(j).resize(in.Width / 50.f);

	for (int y = 0; y < _map.size(); y++)
	{
		for (int x = 0; x < _map.at(y).size(); x++)
		{
			_map[y][x] = '0';
		}
	}
	for (int y = 0; y < _map.size(); y++)
	{
		for (int x = 0; x < _map.at(y).size(); x++)
		{
			if (_map[y][x] == '0')
				file >> _map[y][x];
			else
				break;




			switch (_map[y][x])
			{
			case 'w':
			{
				Sprite* spr = new Sprite();
				spr->initWithFile(L"wall.png");
				spr->_position = getPosByTile(Vec2(x, y), spr->_texture->_info);
				pa->addChild(spr);
				spr->_name = L"build";

				for (int i = 0; i < spr->_texture->_info.Width / 50; i++)
					_map[y][x + i] = 'w';
			}
			break;
			}




		}
	}
	_size.x = _map.at(0).size();
	_size.y = _map.size();

	file.close();
}

Vec2 Tile::getPosByTile(Vec2 tile, D3DXIMAGE_INFO i)
{
	Vec2 tilei = tile;

	tilei.x *= 50;
	tilei.y *= 50;

	tilei.y += 50;

	tilei.x += i.Width / 2;
	tilei.y -= i.Height / 2;

	return tilei;
}

Vec2 Tile::getTileByPos(Vec2 pos, D3DXIMAGE_INFO i)
{
	Vec2 posi = pos;

	posi.x -= i.Width / 2;
	posi.y += i.Height / 2;

	posi.y -= 50;

	posi.x /= 50;
	posi.y /= 50;

	return posi;
}