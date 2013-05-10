#ifndef SPRITE_H
#define SPRITE_H

#include <vector>

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <SDL.h>

#include "Utils.h"
#include "Resource.h"
#include "Surface.h"


#include "prologue.h"
#define SPRITE_DECAL	0
#define SPRITE_OPAQUE	1
#define SPRITE_TRANSC	2
class G_DECLSPEC Sprite : public Surface
{
public:
	
	static vector<Sprite*> objects;

	bool visible;

	GLuint id();


	Sprite( char	*src =		NULL,
			Surface *parent =	NULL,
			double	 posx =		0,
			double	 posy =		0);
	virtual ~Sprite();

	
	static SDL_Surface* loadBmp	(char *src);
	static GLuint newTexture	(SDL_Surface *surface);
	static GLuint newTexture	(char *src);

	static void deleteBmp		(SDL_Surface *surface);
	static void deleteTexture	(GLuint id);
	void deleteTexture			();
	
	void setTexture(GLuint id);
	void setTexture(SDL_Surface *surface);
	void setTexture(char *src);

private:

	GLuint _id;

	void Sprite_display();
};
#include "epilogue.h"

#endif