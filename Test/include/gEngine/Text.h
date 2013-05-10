#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Utils.h"
#include "Surface.h"
#include "Sprite.h"


#include "prologue.h"
class G_DECLSPEC Text : public Sprite
{
public:

	static vector<Text*> objects;


	string	text();
	int		textSize();
	int		textColorR();
	int		textColorG();
	int		textColorB();

	void	text(string txt);
	void	textSize(int size);
	void	textColor(int r,int g,int b);
	void	textStyle(int style);
	void	textFont(char *font);


	Text(string	txt =		NULL,
		Surface *parent =	NULL,
		double	posx =		0,
		double	posy =		0,
		int		fontSize =	12,
		int		red =		255,
		int		green =		255,
		int		blue =		255,
		int		style =		TTF_STYLE_NORMAL,
		char	*font =		"segoeui.ttf");
	~Text();
private:

	static bool TTFinitialized;


	string		_text;
	int			_size;
	SDL_Color	_color;
	int			_style;
	TTF_Font	*_font;
	char*		_fontFile;


	TTF_Font*	newFont(char *font,int fontSize);

	void		setFont(TTF_Font *font);
	void		setFont(char *font);
	void		setFont(char *font,int fontSize);
	void		setFontSize(int fontSize);
	void		setFontStyle(int style);
	void		setFontColor(int r,int g,int b);
	void		refreshTextTexture();

	void TTFinit();
};
#include "epilogue.h"

#endif