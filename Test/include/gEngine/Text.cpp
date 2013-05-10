#include "Text.h"
using namespace utils;


vector<Text*>	Text::objects;
bool			Text::TTFinitialized = false;

string	Text::text()		{ return _text;		}
int		Text::textSize()	{ return _size;		}
int		Text::textColorR()	{ return _color.r;	}
int		Text::textColorG()	{ return _color.g;	}
int		Text::textColorB()	{ return _color.b;	}

void Text::text(string txt)
{
	_text = txt;
	refreshTextTexture();
}
void Text::textSize(int size)
{
	setFontSize(size);
	refreshTextTexture();
}
void Text::textColor(int r,int g,int b)
{
	setFontColor(r,g,b);
	refreshTextTexture();
}
void Text::textStyle(int style)
{
	setFontStyle(style);
	refreshTextTexture();
}
void Text::textFont(char *font)
{
	setFont(font);
	refreshTextTexture();
}



Text::Text(	string	txt,
			Surface *parent,
			double	posx,
			double	posy,
			int		fontSize,
			int		red,
			int		green,
			int		blue,
			int		style,
			char	*font) : Sprite(NULL,parent,posx,posy)
{
	objects.push_back(this);

	TTFinit();

	_text =		txt;
	_size =		fontSize;
	_font =		NULL;
	_style =	style;
	_fontFile = font;

	setFont(font,fontSize);
	setFontColor(red,green,blue);
	setFontStyle(style);

	refreshTextTexture();
}
Text::~Text()
{
	if(_font) TTF_CloseFont(_font);
	removeObject(*this,objects);
}



TTF_Font* Text::newFont(char *font,int fontSize)
{
	void *mem = 0;
	int size;

	Resource::fetch(font,&mem,&size);

	if(!mem) return NULL;

	SDL_RWops *data = SDL_RWFromMem(mem,size*sizeof(char));
	return TTF_OpenFontRW(data,0,fontSize);
}

void Text::setFont(TTF_Font *font)
{
	if(_font) TTF_CloseFont(_font);
	_font = font;
}
void Text::setFont(char *font)
{
	_fontFile = font;
	setFont(newFont(font,_size));
}
void Text::setFont(char *font,int fontSize)
{
	_fontFile = font;
	_size =		fontSize;
	setFont(newFont(font,fontSize));
}
void Text::setFontSize(int fontSize)
{
	_size = fontSize;
	setFont(newFont(_fontFile,fontSize));
}
void Text::setFontStyle(int style)
{
	if(_font)
	{
		_style = style;
		TTF_SetFontStyle(_font,style);
	}
}
void Text::setFontColor(int r,int g,int b)
{
	_color.r = r;
	_color.g = g;
	_color.b = b;
}
void Text::refreshTextTexture()
{	
	if(_font && _text.size() > 0)
	{
		SDL_Surface *surface = TTF_RenderText_Blended(_font,_text.c_str(),_color);
		if(surface)
		{
			deleteTexture(id());
			setTexture(surface);
			deleteBmp(surface);
		}
	}
}



void Text::TTFinit()
{
	if(!TTFinitialized)
	{
		TTF_Init();
		TTFinitialized = true;
	}
}