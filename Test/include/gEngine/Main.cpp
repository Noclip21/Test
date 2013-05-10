#include "Main.h"



bool	Main::RUNNING =		 false;

int		Main::_FRAMERATE =	 0;
int		Main::_FPS =		 0;

double	Main::_TIME =		 0;
double	Main::_SPEEDFACTOR = 0;


int		Main::framerate()	{ return _FRAMERATE;	}
int		Main::fps()			{ return _FPS;			}
double	Main::time()		{ return _TIME;			}
double	Main::speedFactor() { return _SPEEDFACTOR;	}

int Main::_w = 0;
int Main::_h = 0;

int Main::width() { return _w; }
int Main::height(){ return _h; }



Main::Main(int	w,
		   int	h,
		   int	framerate,
		   bool frame,
		   char *appName)
{
	_w =			w;
	_h =			h;
	_FRAMERATE =	framerate;
	_TIME =			1;
	_appName =		appName;
	_frame =		frame;

	if(init()) RUNNING = true;
}

Main::~Main()
{
	// code
}


bool Main::init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;


	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
 
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
 
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,8);
 
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);
 
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,2);


	int flags = SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL;
	if(!_frame) flags = flags | SDL_NOFRAME;
	SDL_Surface *surface;
    if((surface = SDL_SetVideoMode(_w,_h,32,flags)) == NULL)
		return false;


	glClearColor(0,0,0,0);
	glClearDepth(1.0f);
 
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


	SDL_WM_SetCaption(_appName,_appName);

	new Event();

    return true;
}
int Main::display()
{
	int timer =		0;
	int	oldTime	=	0;
	int	lastTime =	0;
	int	frames =	0;


	while(RUNNING)
	{
		if((int)(SDL_GetTicks() - timer) > 1000/_FRAMERATE)
		{
			timer = SDL_GetTicks();
			if(SDL_GetTicks() - oldTime > 1000)
			{
				oldTime = SDL_GetTicks();
				_FPS = frames;
				frames = 0;
			}
			_SPEEDFACTOR =	((SDL_GetTicks() - lastTime)/1000.0f)*_FRAMERATE;
			lastTime =		SDL_GetTicks();
			frames++;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for(size_t i=0; i<Object::objects.size(); ++i)
				if(Object::objects[i]) Object::objects[i]->display();

			SDL_GL_SwapBuffers();
		}
	}


	quit();

	return 0;
}
void Main::quit()
{
	while(Object::objects.size()) delete Object::objects[0];
	SDL_Quit();
}