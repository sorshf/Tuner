#include <SDL3/SDL.h>
#ifndef SOUND_H
#define SOUND_H


class Sound {
    private:
        float* data_ = nullptr;
        int datasize_ = 0;
        int sampleRate_ = 0;
        float* xCorr_ = nullptr;
    public:
        Sound(int datasize, int sampleRate);
        ~Sound();
        void update(SDL_AudioStream* stream);
        float getFreq();
        char* getFreqStr();
        int getSize() const;
        float* getData() const;
};


#endif