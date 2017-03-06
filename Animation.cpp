#include "DXUT.h"
#include "Sprite.h"
#include "Animation.h"

void Animation::initAnimation(Sprite* t, float d, bool l, bool e)
{
	_target = t;
	_delay = 0;
	_maxdelay = d;
	_loop = l;
	_erase = e;
	_run = true;
	_endfunc = nullptr;
}

void Animation::addClips(std::wstring str)
{
	_clips.push_back(TextureMng::getInstance()->getTexture(str));
}

void Animation::removeClipAll()
{
	_delay = 0;
	_idx = 0;
	_clips.clear();
}

void Animation::update()
{ 
	if (_clips.size() == 0)
		return;

	_delay += Time::dt;
	if (_delay >= _maxdelay)
	{
		_delay = 0;
		_idx++;

		if (_idx >= _clips.size())
		{
			if (_loop)
				_idx = 0;
			else
			{
				if (_endfunc)
					_endfunc();

				if (_erase)
					_target->removeChild(_target);
				else
					_run = false;
				return;
			}
		}

		_target->_texture = _clips.at(_idx);
	}
}