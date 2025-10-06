#include "Sound.h"
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

void xCorr(float sig1[], int sig1Size, float sig2[], int sig2Size, float xCorrCoef[]) {

    int xCorrCoefCounter = 0;

    int lagMin = 0;
    int lagMax = sig1Size -1;

    for (int lag = lagMin; lag <= lagMax; lag++) {
        float sum = 0;

        for (int coef1 = 0; coef1 < sig1Size; coef1++) {
            int coef2 = coef1 - lag;
            // Checking if coef2 is valid given the lag
            if (coef2 >= 0 && coef2<= sig1Size - 1) {
                sum += sig1[coef1] * sig2[coef2];
            }
        }

        xCorrCoef[xCorrCoefCounter] = sum;
        xCorrCoefCounter++;
    }

}

float ACFFrequency(float sig1[], int sig1Size, int sampleRate, float xCorrs[]){
    //Autocorrelation
    xCorr(sig1, sig1Size, sig1, sig1Size, xCorrs);

    //Find the peaks
    vector<float> peaks;
    //Skipping i=0
    for (int i = 1; i < sig1Size-1; i++) {
        if ((xCorrs[i+1] < xCorrs[i]) && (xCorrs[i-1] < xCorrs[i])) {
            peaks.push_back(i);
        }
    }

    if (peaks.size() < 2)
    {
        return -1.0;
    }
    

    //Find the frequencies
    vector<float> freqs;
    for (size_t i = 0; i < peaks.size()-1; i++) {
        freqs.push_back(sampleRate/(peaks[i+1]-peaks[i]));
    }

    //Find the average of the frequencies
    float sum_freq = 0.0;

    for (float val: freqs) {
        sum_freq += val;
    }

    return sum_freq/freqs.size();
}


Sound::Sound(int datasize, int sampleRate) {
    datasize_ = datasize;
    data_ = new float[datasize];
    xCorr_ = new float[datasize];
    sampleRate_ = sampleRate;
}

Sound::~Sound() {
    if (data_ != nullptr) {
        delete [] data_;
    }

    if (xCorr_ != nullptr) {
        delete [] xCorr_;
    }
}

void Sound::update(SDL_AudioStream* stream){
    SDL_GetAudioStreamData(stream, data_, sizeof(float)*datasize_);
};

float Sound::getFreq() {

    float freq = ACFFrequency(data_, datasize_, sampleRate_, xCorr_);
    return freq;
    
}

char* Sound::getFreqStr() {

    float freq = ACFFrequency(data_, datasize_, sampleRate_, xCorr_);
    char* str;
    SDL_asprintf(&str, "%.2f Hz", freq);
    return str;
    
}

int Sound::getSize() const {
    return datasize_;
}

float* Sound::getData() const {
    return data_;
}