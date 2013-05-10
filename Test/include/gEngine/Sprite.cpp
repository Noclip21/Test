#include "Sprite.h"
using namespace utils;



vector<Sprite*> Sprite::objects;


GLuint Sprite::id(){ return _id; }



Sprite::Sprite( char	 *src,
				Surface	*parent,
				double	 posx,
				double	 posy) : Surface(parent,posx,posy)
{
	objects.push_back(this);

	if(src) setTexture(src);

	visible = true;
	
	addListener([this](){Sprite_display();});
}

Sprite::~Sprite()
{
	if(_id) deleteTexture();
	removeObject(*this,objects);
}



SDL_Surface* Sprite::loadBmp(char *src)
{
	if(!src) return NULL;

	void *mem = 0;
	int size;
	Resource::fetch(src,&mem,&size);
	if(!mem) return NULL;

	SDL_RWops *data = SDL_RWFromMem(mem,size*sizeof(char));
	if(!data) return NULL;
	
	SDL_Surface *temp = SDL_LoadBMP_RW(data,0);
	SDL_FreeRW(data);
	if(!temp) return NULL;
	
	SDL_LockSurface(temp);

	Uint8 keyRed8	= temp->format->palette->colors[255].r;
	Uint8 keyGreen8	= temp->format->palette->colors[255].g;
	Uint8 keyBlue8	= temp->format->palette->colors[255].b;

	SDL_UnlockSurface(temp);

				
	int mode = 0;
	if(src[0] == '{')
		mode = SPRITE_DECAL;
	else
		if((keyRed8 + keyGreen8 + keyBlue8) == 255)
				mode = SPRITE_TRANSC;
		else
				mode = SPRITE_OPAQUE;
				
	switch(mode)
	{
		case SPRITE_OPAQUE:
		{
			SDL_Surface *formated = SDL_DisplayFormatAlpha(temp);
			deleteBmp(temp);
			return formated;
		}

		case SPRITE_TRANSC:
		{
			SDL_SetColorKey(temp,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(temp->format,keyRed8,keyGreen8,keyBlue8));
			SDL_Surface *formated = SDL_DisplayFormatAlpha(temp);
			deleteBmp(temp);
			return formated;
		}
		case SPRITE_DECAL:
		{
			SDL_Surface *formated = SDL_DisplayFormatAlpha(temp);
			deleteBmp(temp);

			SDL_LockSurface(formated);
			
			int w = formated->w;
			int h = formated->h;
			Uint32 *pixels = (Uint32*)formated->pixels;

			Uint32 keyColor32 = SDL_MapRGB(formated->format,keyRed8,keyGreen8,keyBlue8);
				Uint8 keyRed32 =	(keyColor32 & 0x00ff0000) >> 16;
				Uint8 keyGreen32 =	(keyColor32 & 0x0000ff00) >> 8;
				Uint8 keyBlue32 =	 keyColor32 & 0x000000ff;

			for(int x=0; x<w; ++x)
				for(int y=0; y<h; ++y)
				{
					Uint32 *pixel = &pixels[(y*w)+x];

					Uint8 alpha =	(*pixel & 0xff000000) >> 24;
					Uint8 red =		(*pixel & 0x00ff0000) >> 16;
					Uint8 green =	(*pixel & 0x0000ff00) >> 8;
					Uint8 blue =	 *pixel & 0x000000ff;
					
					Uint8 grayscale = (Uint8)((red+green+blue)/3);

					*pixel = SDL_MapRGBA(formated->format,
						min(grayscale,keyRed32),
						min(grayscale,keyGreen32),
						min(grayscale,keyBlue32),
						255-grayscale);
				}

			SDL_UnlockSurface(formated);
			return formated;
		}
		default:
			return NULL;
	}
}

GLuint Sprite::newTexture(SDL_Surface *surface)
{
	if(!surface) return NULL;

	Uint8 bpp = surface->format->BytesPerPixel;
	GLenum format;
	if(bpp == 4)
		if(surface->format->Rmask == 0x000000ff) format = GL_RGBA;
		else									 format = GL_BGRA_EXT;
	if(bpp == 3)
		if(surface->format->Rmask == 0x000000ff) format = GL_RGB;
		else									 format = GL_BGR_EXT;

	GLuint id = 0;
	glGenTextures(1,&id);

	glBindTexture(GL_TEXTURE_2D,id);
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
 
		glTexImage2D(GL_TEXTURE_2D,0,bpp,surface->w,surface->h,0,
					format,GL_UNSIGNED_BYTE,surface->pixels);
	}
	
	return id;
}

GLuint Sprite::newTexture(char *src)
{
	SDL_Surface *surface = loadBmp(src);
	
	if(!surface) return NULL;
	
	GLuint id = newTexture(surface);
	deleteBmp(surface);

	return id;
}



void Sprite::deleteBmp(SDL_Surface *surface)
{
	SDL_FreeSurface(surface);
}

void Sprite::deleteTexture(GLuint id)
{
	if(id) glDeleteTextures(1,&id);
}

void Sprite::deleteTexture()
{
	deleteTexture(_id);
}



void Sprite::setTexture(GLuint id)
{
	_id = id;

	glBindTexture(GL_TEXTURE_2D,_id);
	{
		glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&_width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT,&_height);
	}
}

void Sprite::setTexture(SDL_Surface *surface)
{
	setTexture(newTexture(surface));
}

void Sprite::setTexture(char *src)
{
	setTexture(newTexture(src));
}



void Sprite::Sprite_display()
{
	// code
}