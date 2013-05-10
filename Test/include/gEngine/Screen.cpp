#include "Screen.h"



vector<Screen*> Screen::objects;


Camera* Screen::cam(){ return _cam; }

void Screen::cam(Surface *wrapper,Surface *target)
{
	if(alive(wrapper) && alive(target))
	{
		if(alive(_cam)) _cam->kill();
		_cam = new Camera(width(),height(),wrapper);
		_cam->target(target);
	}
}
void Screen::cam(Surface *wrapper,vector2 position)
{
	if(alive(wrapper))
	{
		if(alive(_cam)) _cam->kill();
		_cam = new Camera(width(),height(),wrapper);
		_cam->target(position);
	}
}
void Screen::camDelay(double delay)
{
	if(alive(_cam)) _cam->delay = delay;
}



Screen::Screen(	Surface *parent,
				double	 posx,
				double	 posy,
				int		 width,
				int		 height) : Surface(parent,posx,posy)
{
	objects.push_back(this);
	
	_width =	width;
	_height =	height;

	_cam = NULL;

	addListener([this](){Screen_display();});
}

Screen::~Screen()
{
	if(_cam)_cam->kill();
	removeObject(*this,objects);
}



void Screen::blint(Sprite *sprite)
{
	if(alive(sprite))
	{
		if(sprite->visible)
		{
			glBindTexture(GL_TEXTURE_2D,sprite->id());
			{
				vector2 p =		sprite->globalPos() - globalPos();
				vector2 o =		sprite->globalOrigin()*sprite->scale;
				double rot =	sprite->globalRotation();
				float r =		sprite->globalRed();
				float g =		sprite->globalGreen();
				float b =		sprite->globalBlue();
				float a =		sprite->globalAlpha();
				double w =		sprite->width()*sprite->scale.x;
				double h =		sprite->height()*sprite->scale.y;
					
				double sn = sin(rot*PI/180);
				double cn = cos(rot*PI/180);
				
				GLfloat	qx = -cn*o.x+sn*o.y,			qxw = cn*(w-o.x)+sn*o.y,
						qy = -sn*o.x-cn*o.y,			qyw = sn*(w-o.x)-cn*o.y,

						qxh = -cn*o.x-sn*(h-o.y),		qxwh = cn*(w-o.x)-sn*(h-o.y),
						qyh = -sn*o.x+cn*(h-o.y),		qywh = sn*(w-o.x)+cn*(h-o.y);
				
				
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glBegin(GL_QUADS);
					glColor4f(r,g,b,a);
					glTexCoord2f(0,0);	glVertex3f(p.x+qx,	p.y+qy,0);
					glTexCoord2f(1,0);	glVertex3f(p.x+qxw,	p.y+qyw,0);
					glTexCoord2f(1,1);	glVertex3f(p.x+qxwh,p.y+qywh,0);
					glTexCoord2f(0,1);	glVertex3f(p.x+qxh,	p.y+qyh,0);
				glEnd();
			}
		}
	}
}

void Screen::render(Surface* surface)
{
	if(alive(surface))
		for(size_t i=0; i<surface->children.size(); ++i)
		{
			if(!dynamic_cast<Screen*>(surface->children[i]))
			{
				if(dynamic_cast<Sprite*>(surface->children[i]))
					blint((Sprite*)surface->children[i]);
				render(surface->children[i]);
			}
		}
}



void Screen::Screen_display()
{
	glViewport(	globalPos().x,
				Main::height()-_height-globalPos().y,
				_width,
				_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,_width,_height,0,1,-1);

	render(this);
}