#include "Audio.h"
using namespace utils;



vector<Audio*>	Audio::objects;
bool			Audio::_alutInitalized = false;

bool Audio::playing()
{
	int value;
	alGetSourcei(_source,AL_SOURCE_STATE,&value);
	return (value == AL_PLAYING);
}



Audio::Audio(char *src,bool loop)
{
	objects.push_back(this);

	init();

	if(src)
	{
		loadBuffer(src);
		if(_buffer)
		{
			createSource();
			setLoop(loop);
		}
	}
}
Audio::~Audio()
{
	unload();

	removeObject(*this,objects);
	if(objects.size() <= 0) exit();
}



void Audio::play()	{ alSourcePlay(_source);	}
void Audio::stop()	{ alSourceStop(_source);	}
void Audio::rewind(){ alSourceRewind(_source);	}
void Audio::pause()	{ alSourcePause(_source);	}

void Audio::setLoop(bool loop)		{ alSourcei(_source,AL_LOOPING,loop);	}
void Audio::setVolume(float volume) { alSourcef(_source,AL_GAIN,volume);	}



void Audio::loadBuffer(char *src)
{
	alGenBuffers(1,&_buffer);
	
	void *data = 0;
	int	size;
	Resource::fetch(src,&data,&size);

	if(data)
	{
		_buffer = alutCreateBufferFromFileImage(data,size);
		alBufferData
		(
			_buffer,
			_format,
			_data,
			_size,
			_freq
		);
	}
}
void Audio::createSource()
{
	if(_buffer)
	{
		alGenSources(1,&_source);
		alSourcei(_source,AL_BUFFER,_buffer);
	}
}
void Audio::unload()
{
	if(_source) alDeleteSources(1,&_source);
	if(_buffer) alDeleteBuffers(1,&_buffer);
}



void Audio::init()
{
	if(!_alutInitalized)
	{
		alutInit(0,NULL);
		_alutInitalized = true;
	}
}
void Audio::exit()
{
	if(_alutInitalized)
	{
		alutExit();
		_alutInitalized = false;
	}
}