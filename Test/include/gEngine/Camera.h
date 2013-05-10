#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include "Utils.h"
#include "Object.h"
#include "Surface.h"

using namespace utils;


#include "prologue.h"
class G_DECLSPEC Camera : public Object
{
public:

	static vector<Camera*> objects;


	double delay;
	
	
	Surface* target();
	void	 target(Surface *target);
	void	 target(vector2 pos);

	
	Camera(	int		 screenWidth,
			int		 screenHeight,
			Surface *wrapper);
	~Camera();

private:

	Surface	*_wrapper;
	Surface *_target;
	vector2 _offset;
	vector2	_pos;

	void Camera_display();
};
#include "epilogue.h"

#endif