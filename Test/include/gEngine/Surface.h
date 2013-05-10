#ifndef Surface_H
#define Surface_H

#include <vector>

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <SDL.h>

#include "Main.h"
#include "Utils.h"
#include "Object.h"


#include "prologue.h"
class G_DECLSPEC Surface : public Object
{
public:

	static vector<Surface*> objects;

	vector<Surface*> children;
	
	vector2 pos;
	vector2 avel;
	vector2 origin;
	vector2 scale;
	double rotation;
	double avelrot;

	float red;
	float green;
	float blue;
	float alpha;
	
	
	vector2 globalPos();
	vector2 globalOrigin();
	double	globalRotation();
	float	globalRed();
	float	globalGreen();
	float	globalBlue();
	float	globalAlpha();
	vector2 mouse();
	vector2	oldPos();
	double	oldrot();
	int		depth();
	Surface*parent();
	int		width();
	int		height();
	
	void pos2d		(double posx,double posy);
	void avel2d		(double ax,double ay);
	void origin2d	(double posx,double posy);
	void scale2d	(double sx,double sy);
	void parent		(Surface *parent);


	Surface(Surface *parent =	NULL,
			double	posx =		0,
			double	posy =		0);
	virtual ~Surface();


	void swapDepths		(int surfaceId1,int surfaceId2);
	void addChild		(Surface *child);
	void removeChild	(Surface *child);


protected:

	int _width;
	int _height;


private:

	int _depth;
	
	Surface	*_parent;

	vector2 _oldpos;
	double _oldrot;

	void Surface_display();
};
#include "epilogue.h"

#endif