#ifndef AUDIO_H
#define AUDIO_H

#include <al.h>
#include <alut.h>

#include "Object.h"
#include "Resource.h"
#include "Utils.h"



#include "prologue.h"
class G_DECLSPEC Audio : public Object
{
public:

	static vector<Audio*> objects;

	bool playing();


	Audio(char *src,bool loop = false);
	~Audio();

	void play();
	void stop();
	void rewind();
	void pause();

	void setLoop(bool loop);
	void setVolume(float volume);


protected:

	void loadBuffer(char *src);
	void createSource();
	void unload();

private:

	ALuint		_buffer;
	ALenum		_format;
	ALsizei		_size;
	ALfloat		_freq;
	ALvoid		*_data;
	ALboolean	_looping;

	ALuint _source;

	static bool _alutInitalized;
	void init();
	void exit();

};
#include "epilogue.h"

#endif