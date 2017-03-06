#include "DXUT.h"
#include "Sprite.h"
#include "Director.h"

TextureMng* TextureMng::_tinstance = NULL;

void Sprite::draw()
{
	Node::draw();

	if (!_texture)
		return;

	if (ani._run)
		ani.update();

	Director::_sprite->Begin(D3DXSPRITE_ALPHABLEND);
	Director::_sprite->SetTransform(&getMatrix());
	D3DXVECTOR3 center = { _texture->_info.Width * _anchor.x, _texture->_info.Height * _anchor.y, 0 };
	Director::_sprite->Draw(_texture->_texture, NULL, &center, NULL, _color);
	Director::_sprite->End();

}