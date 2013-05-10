#include "Object.h"
using namespace utils;



vector<Object*> Object::objects;

bool Object::alive(Object *obj)
{
	if(findObject(*obj,objects) >= 0) return true;
	else							  return false;
}



Object::Object()
{
	objects.push_back(this);
	markedToDeath = false;
}

Object::~Object()
{
	removeObject(*this,objects);
}



void Object::addListener(function<void ()> f)
{
	listeners.push_back(f);
}

void Object::display()
{
	if(!markedToDeath)
	{
		for(size_t i=0; i<listeners.size(); ++i)
			if(listeners[i]) listeners[i]();
	}else
		delete this;
}

void Object::kill()
{
	markedToDeath = true;
}