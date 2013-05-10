#include "Surface.h"
#include "Main.h"
using namespace utils;



vector<Surface*> Surface::objects;


vector2 Surface::globalPos()		{ return _parent?pos+_parent->globalPos()			:pos;		}
vector2 Surface::globalOrigin()		{ return _parent?origin+_parent->globalOrigin()		:origin;	}
double	Surface::globalRotation()	{ return _parent?rotation+_parent->globalRotation()	:rotation;	}
float	Surface::globalRed()		{ return _parent?red+_parent->globalRed()			:red;		}
float	Surface::globalGreen()		{ return _parent?green+_parent->globalGreen()		:green;		}
float	Surface::globalBlue()		{ return _parent?blue+_parent->globalBlue()			:blue;		}
float	Surface::globalAlpha()		{ return _parent?alpha*_parent->globalAlpha()		:alpha;		}
vector2 Surface::mouse()			{ return Event::mouse-globalPos();								}
vector2	Surface::oldPos()			{ return _oldpos;												}
double	Surface::oldrot()			{ return _oldrot;												}
int		Surface::depth()			{ return _depth;												}
Surface*Surface::parent()			{ return _parent;												}
int		Surface::width()			{ return _width;												}
int		Surface::height()			{ return _height;												}








void Surface::pos2d		(double posx,double posy)	{ pos = vector2(posx,posy);		}
void Surface::avel2d	(double ax,double ay)		{ avel = vector2(ax,ay);		}
void Surface::origin2d	(double posx,double posy)	{ origin = vector2(posx,posy);	}
void Surface::scale2d	(double sx,double sy)		{ scale = vector2(sx,sy);		}
void Surface::parent(Surface *parent)
{
	if(_parent) _parent->removeChild(this);
	if(parent)	_parent->addChild(this);
}



Surface::Surface(Surface *parent,
				 double	  posx,
				 double	  posy)
{
	objects.push_back(this);
	
	_oldpos = pos = vector2(posx,posy);
	scale = vector2(1,1);

	rotation =	0;
	avelrot =	0;
	red =		1;
	green =		1;
	blue =		1;
	alpha =		1;
	
	_depth =	-1;
	_parent =	NULL;
	_width =	0;
	_height =	0;
	_oldrot =	0;

	if(parent) parent->addChild(this);

	addListener([this](){Surface_display();});
}
Surface::~Surface()
{
	while(children.size() > 0) delete children[0];

	if(alive(_parent))
	{
		removeObject(*this,_parent->children);
		for(size_t i=_depth; i<_parent->children.size(); ++i)
			_parent->children[i]->_depth = _depth;
	}

	removeObject(*this,objects);
}



void Surface::swapDepths(int depth1,int depth2)
{
	if(children.size() > 1)
	{
		if( (depth1 >= 0 && depth2 < (int)children.size()) &&
			(depth1 >= 0 && depth2 < (int)children.size()) &&
			(depth1 != depth2))
		{
			children[depth1]->_depth = depth2;
			children[depth2]->_depth = depth2;

			Surface *temp = children[depth1];
			children[depth1] = children[depth2];
			children[depth2] = temp;
		}
	}
}
void Surface::addChild(Surface *child)
{
	if(alive(child))
	{
		child->_depth = children.size();
		children.push_back(child);
		child->_parent = this;
	}
}
void Surface::removeChild(Surface *child)
{
	if(alive(child))
	{
		removeObject(*child,children);
		child->_parent = NULL;
		child->_depth = -1;
	}
}



void Surface::Surface_display()
{
	_oldpos = pos;
	_oldrot = rotation;

	double coef = Main::speedFactor()*Main::time();

	pos =		pos+avel*coef;
	rotation += avelrot*coef;
}