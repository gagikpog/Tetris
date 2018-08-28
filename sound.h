#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <stdio.h>
#include <string>

#ifndef SOUND_H
#define SOUND_H

class Sound
{
private:
	std::string filename;
	ALCdevice* device;
	ALuint buffer, source;
	bool pause = false;
	float volume = 100;
public:
	Sound();
	~Sound();
	void Open(std::string filename);
	void Play();
	void Pause();
	void Stop();
	void Update();
	void setVolume(int volume);
	int getVolume();
	bool Loop = true;
};

#endif