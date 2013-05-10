#include"Camera.h"



vector<Camera*> Camera::objects;


Surface* Camera::target()				{ return _target;	}
void	 Camera::target(Surface *target){ _target = target; }
void	 Camera::target(vector2 pos)
{
	_target =	NULL;
	_pos =		pos;
}



Camera::Camera(int screenWidth,
			   int screenHeight,
			   Surface *wrapper)
{
	objects.push_back(this);

	delay = 0.9f;

	_offset = vector2(screenWidth/2,screenHeight/2);
	_wrapper = wrapper;

	addListener([this](){Camera_display();});
}

Camera::~Camera()
{
	_wrapper =	NULL;
	_target =	NULL;
	removeObject(*this,objects);
}



void Camera::Camera_display()
{
	if(alive(_wrapper))
	{
		vector2 pos;
		if(alive(_target))	pos = _target->pos;
		else				pos = _pos;

		_wrapper->avel = (_offset - pos - _wrapper->pos)*(1-delay);
	}
}