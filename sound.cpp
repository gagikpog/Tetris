#include "sound.h"

// gcc -o simplealut simplealut.c `pkg-config --libs freealut`
//

#define FILENAME "sound.wav"

void sound()
{

    ALuint buffer, source;
    ALint state;

    // Initialize the environment
    alutInit(0, NULL);

    // Capture errors
    alGetError();

    // Load pcm data into buffer
    buffer = alutCreateBufferFromFile(FILENAME);

    // Create sound source (use buffer to fill source)
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

    // Play
    alSourcePlay(source);

    // Wait for the song to complete
    //do {
    //    alGetSourcei(source, AL_SOURCE_STATE, &state);
    //} while (state == AL_PLAYING);

    // Clean up sources and buffers
    //alDeleteSources(1, &source);
    //alDeleteBuffers(1, &buffer);

    // Exit everything
    //alutExit();

    return;
}
