#include "Recorder.h"


Recorder::Recorder(int sampleRate, int bufferDuration_ms):
    m_sampleRate(sampleRate), 
    m_soundDataSize(sampleRate * bufferDuration_ms / 1000),
    m_minBuffSize(m_soundDataSize * sizeof(float)), //in bytes
    m_sound(m_soundDataSize, m_sampleRate)

{
    if(!SDL_Init(SDL_INIT_AUDIO)){
        failed = true;
    };


    //Create Audio Recording stream
    m_spec.channels = 1;
    m_spec.format = SDL_AUDIO_F32;
    m_spec.freq = m_sampleRate;

    m_recordStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_RECORDING, &m_spec, NULL, NULL);
    if (m_recordStream == NULL) {
        std::cerr << "Couldn't initiate the audio recorder stream: " << SDL_GetError() << std::endl;
        failed = true;
    } else {
        failed = false;
        SDL_ResumeAudioStreamDevice(m_recordStream);
    }


}

Recorder::~Recorder() {
    //Not sure why I shouldn't do this!!!
    // if (m_recordStream) {

    //     SDL_DestroyAudioStream(m_recordStream);
    // }
}

bool Recorder::record() {

    // If we have enough data (BUFFER_DURATION_ms) in the buffer the sound is updated
    if (SDL_GetAudioStreamAvailable(m_recordStream) >= m_minBuffSize) {
        m_sound.update(m_recordStream); 
        return true;
    }

    return false;
}


Sound& Recorder::getSound()  {
    return m_sound;
}

