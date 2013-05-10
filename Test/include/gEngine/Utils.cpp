/*#include <vector>

#include "Utils.h"

using namespace std;


template <class T>
int Utils::findObject<T>(T &obj,vector<T*> &v)
{
	for(size_t i=0; i < v.size(); i++)
		if(&obj == v[i]) return i;
	return -1;
}

template <class T>
bool Utils::removeObject<T>(T &obj,vector<T*> &v)
{
	int pos = findObject(obj,v);
	if(pos >= 0)
	{
		v.erase(v.begin()+pos);
		return true;
	}
	return false;
}*/