#include "Sound.h"
#include <iostream>
Sound::Sound()
{
    device = alcOpenDevice(NULL);
}

Sound::~Sound()
{
    //Clean up sources and buffers
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcCloseDevice(device);
    alutExit();
}

void Sound::Open(std::string fname)
{
    if(filename != "")
    {
        //Clean up sources and buffers
        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
    }
    filename = fname;

    // Initialize the environment
    alutInit(0, NULL);
    
    // Capture errors
    alGetError();

    // Load pcm data into buffer
    buffer = alutCreateBufferFromFile(filename.c_str());

    // Create sound source (use buffer to fill source)
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    setVolume(volume);
}

void Sound::Play()
{
    if(!active)
        return;
    pause = false;
    alSourcePlay(source);
}

void Sound::Pause()
{
    pause = true;
    alSourcePause(source);
}

void Sound::Stop()
{
    alSourceStop(source);
}

void Sound::Update()
{
    if(!Loop || pause || !active)
        return;
    if (getStatus() != AL_PLAYING)
        Play();
}

void Sound::setVolume(int v)
{
    volume = v;
    alSourcef(source, AL_GAIN, volume/100.f);
}

 int Sound::getVolume()
 {
     return volume;
 }

int Sound::getStatus()
{
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state;
}
void Sound::setActive(bool stat)
{
    active = stat;
    if(!active)
    {
        Pause();
    }else {
        if(Loop)
            Play();
    }
}

bool Sound::getActive()
{
    return active;
}