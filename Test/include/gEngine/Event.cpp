#include "Event.h"
using namespace utils;



vector<SDLKey>	Event::_keys;
vector<Uint8>	Event::_buttons;
vector2			Event::mouse;


bool Event::keyDown(int key)
{
	SDLKey keyObj = (SDLKey)key;
	return (findObject(keyObj,_keys) >= 0);
}
bool Event::mouseButtonDown(int buttom)
{
	Uint8 buttomObj = (Uint8)buttom;
	return (findObject(buttomObj,_buttons) >= 0);
}



Event::Event()
{
	addListener([this](){Event_display();});
}
Event::~Event()
{
	// code
}



void Event::Event_display()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
		switch(e.type)
		{
			/*case():
			{
				break;
			}*/

				// key
			case(SDL_KEYDOWN):
			{
				if(findObject(e.key.keysym.sym,_keys) < 0)
					_keys.push_back(e.key.keysym.sym);
				break;
			}
			case(SDL_KEYUP):
			{
				removeObject(e.key.keysym.sym,_keys);
				break;
			}

				// mouse
			case(SDL_MOUSEMOTION):
			{
				mouse.x = e.motion.x;
				mouse.y = e.motion.y;
				break;
			}
			case(SDL_MOUSEBUTTONDOWN):
			{
				if(findObject(e.button.button,_buttons) < 0)
					_buttons.push_back(e.button.button);
				break;
			}
			case(SDL_MOUSEBUTTONUP):
			{
				removeObject(e.button.button,_buttons);
				break;
			}
				
		}
}