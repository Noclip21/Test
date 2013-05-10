#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <vector>
#include <SDL.h>
#include "Object.h"
#include "Utils.h"

using namespace std;
using namespace utils;


#include "prologue.h"
class G_DECLSPEC Event : public Object
{
public:
	
	static vector2 mouse;

	static bool keyDown(int key);
	static bool mouseButtonDown(int buttom);

	Event();
	~Event();

private:

	static vector<SDLKey>	_keys;
	static vector<Uint8>	_buttons;

	void Event_display();
};
#include "epilogue.h"

#endif