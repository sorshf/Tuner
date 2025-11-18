#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "Recorder.h"
#include "Graph.h"
#include "Text.h"

class App
{
private:
    int m_windowWidth;
    int m_windowHeight;
    Recorder m_recorder;
    Text m_text;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    TTF_TextEngine* m_textEngine;
    TTF_Font* m_font;
    Graph m_graph;

public:
    App(const char* title, int width, int height, int sampleRate, int bufferDuration_ms, const char* fontPath, float fontSize);
    ~App();
    void run();
    void update();
    void render();
};

#endif