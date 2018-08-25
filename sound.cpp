#include "sound.h"
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
}

void Sound::Play()
{
    alSourcePlay(source);
}

void Sound::Pause()
{
    alSourcePause(source);
}

void Sound::Stop()
{
    alSourceStop(source);
}

//do {
//        alGetSourcei(source, AL_SOURCE_STATE, &state);
//} while (state == AL_PLAYING);