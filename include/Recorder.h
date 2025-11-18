#ifndef RECORDER_H
#define RECORDER_H

#include <SDL3/SDL.h>
#include "Sound.h"
#include <iostream>

class Recorder
{
private:
    int m_sampleRate;
    int m_soundDataSize; // calculated and initialized in the constructor list
    int m_minBuffSize; // calculated and initialized in the constructor list
    Sound m_sound;
    SDL_AudioSpec m_spec;
    SDL_AudioStream* m_recordStream = nullptr;

public:
    bool failed;
    Recorder(int sampleRate, int bufferDuration_ms);
    ~Recorder();
    bool record();
    Sound& getSound() ;
};

#endif