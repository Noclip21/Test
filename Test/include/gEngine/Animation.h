#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <functional>

#include <SDL.h>

#include "Utils.h"
#include "Object.h"
#include "Surface.h"
#include "Sprite.h"


#include "prologue.h"
class G_DECLSPEC Animation : public Sprite
{
public:

	static vector<Animation*> objects;

	void play();
	void pause();
	void pause(int frame);
	void play(int frame);
	void play(char *name);
	void stop();
	int  numFrames();


	Animation(	Surface *parent = NULL,
				double posx = 0,
				double posy = 0);
	~Animation();
	
	
	void addAnimation(	char	*name,
						int		 time,
						char	*sprites[],
						int		 len);
	void callback(function<void ()> f);

private:

	struct animPack
	{
		char	*name;
		int		 time;
		vector<GLuint> id;
	};

	vector<animPack*>	 _animations;
	animPack			*_currentAnim;
	int					_timer;
	int					_frame;
	bool				_pause;
	function<void ()>	_callback;


	void Animation_display();
};
#include "epilogue.h"

#endif