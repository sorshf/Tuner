#include <SDL3/SDL.h>
#include <iostream>
#include "Graph.h"
#include "Sound.h"
#include <SDL3_ttf/SDL_ttf.h>
#include "Text.h"
#include "Config.h"

using namespace std;


int main() {
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    TTF_Init();

    //Create window
    SDL_Window* window = SDL_CreateWindow("Tuner", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALWAYS_ON_TOP);
    if (window == NULL) {
        cerr << "Couldn't create SDL window: " << SDL_GetError() << endl;
        SDL_Quit();
    }

    //Create Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        cerr << "Couldn't initiate the renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    //Create Audio Recording stream
    SDL_AudioSpec spec;
    spec.channels = 1;
    spec.format = SDL_AUDIO_F32;
    spec.freq = SAMPLE_RATE;

    SDL_AudioStream* recorder = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_RECORDING, &spec, NULL, NULL);
    if (recorder == NULL) {
        cerr << "Couldn't initiate the audio recorder stream: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }
    SDL_ResumeAudioStreamDevice(recorder);

    //Text Engine
    TTF_TextEngine* textEngine = TTF_CreateRendererTextEngine(renderer);
    if (!textEngine) {
        cerr << "Text Engine Error: " << SDL_GetError() << endl;
    }

    TTF_Font* font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!font) {
        cerr << "Font Load Error: " << SDL_GetError() << endl;
    }

    //Text object to show the frequency
    Text t {textEngine, font};
    float xT = (WINDOW_WIDTH - 200) / 2.0; //200 is arbitrary
    float yT = WINDOW_HEIGHT/10.0;
    SDL_Color textColor {255, 255, 255, 255};

    //Recording min buffer size
    const int soundDataSize = SAMPLE_RATE * BUFFER_DURATION_ms / 1000;
    const int minBuffSize = soundDataSize * sizeof(float);

    //Recording data is stored in a Sound object
    Sound s  = Sound(soundDataSize, SAMPLE_RATE);

    //Controling the main loop of the app
    bool quit = false;
    SDL_Event e;

    //Graph
    float graphWidth = 70.0/100.0*WINDOW_WIDTH;
    float graphHeight = 60.0/100.0*WINDOW_HEIGHT;
    float xG = (WINDOW_WIDTH - graphWidth)/2;
    float yG = WINDOW_HEIGHT / 4;

    Graph g {{xG, yG}, graphWidth, graphHeight};

    //Main loop of the app
    while (!quit) {

       while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        // If we have enough data (BUFFER_DURATION_ms) in the buffer
        if (SDL_GetAudioStreamAvailable(recorder) >= minBuffSize) {
            s.update(recorder); 
            g.update(s);
            t.update(s.getFreqStr(), &textColor);
        }

        //Background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Graph
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        g.display(renderer);

        //Text frequency
        t.display(xT, yT);
        
        //Present everything
        SDL_RenderPresent(renderer);

        SDL_Delay(40);

    }

    TTF_DestroyRendererTextEngine(textEngine);
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyAudioStream(recorder);
    TTF_Quit();
    SDL_Quit();
    
}