#include "Animation.h"
using namespace utils;


vector<Animation*> Animation::objects;


void Animation::play()
{
	_pause = false;
}
void Animation::pause()
{
	_pause = true;
} 
void Animation::play(int frame)
{
	_pause = false;
	_frame = frame;
}
void Animation::play(char *name)
{
	if(string(name).compare(_currentAnim->name) != 0)
		for(size_t i=0; i<_animations.size(); ++i)
			if(string(name).compare(_animations[i]->name) == 0)
			{
				stop();
				_currentAnim = _animations[i];
				play();
			}
}
void Animation::pause(int frame)
{
	_pause = true;
	_frame = frame;
}
void Animation::stop()
{
	_pause = true;
	_frame = 0;
	_timer = 0;
}
int Animation::numFrames()
{
	if(_currentAnim)
		return _currentAnim->id.size();
	else
		return 0;
}



Animation::Animation(	Surface *parent,
						double posx,
						double posy) : Sprite(NULL,parent,posx,posy)
{
	objects.push_back(this);

	_currentAnim = NULL;
	_timer = 0;
	_frame = 0;
	_pause = false;
	_callback = [](){};

	addListener([this](){Animation_display();});
}

Animation::~Animation()
{
	for(size_t i=0; i<_animations.size(); ++i)
	{
		for(size_t j=0; j<_animations[i]->id.size(); ++j)
			deleteTexture(_animations[i]->id[j]);
		
		delete _animations[i];
	}
	removeObject(*this,objects);
}




void Animation::addAnimation(char	*name,
							 int	 time,
							 char	*sprites[],
							 int	 len)
{
	if(	!string(name).empty() && time > 0 && len > 0)
	{
		animPack *anim = new animPack;
		anim->name = name;
		anim->time = time;
		for(int i=0; i<len; ++i)
		{
			GLuint id = newTexture(sprites[i]);
			if(id) anim->id.push_back(id);
		}
		_animations.push_back(anim);
		_currentAnim = anim;
		play(0);
	}
}

void Animation::callback(function<void ()> f)
{
	_callback = f;
}

void Animation::Animation_display()
{
	if(_currentAnim)
	{
		if((SDL_GetTicks() - _timer) >= _currentAnim->time)
		{
			_timer = SDL_GetTicks();

			if(_frame >= 0 && _frame < numFrames())
			{
				setTexture(_currentAnim->id[_frame]);
				if(_frame == (numFrames()-1))
					_callback();
			}

			if(!_pause)
			{
				_frame++;
				if(_frame >= numFrames())
					_frame = 0;
			}
		}
	}
}