#include <SDL3/SDL.h>
#include "Sound.h"
#ifndef GRAPH_H
#define GRAPH_H


class Graph {
private:
    float width_;
    float height_;
    SDL_FPoint anchor_;
    SDL_FPoint* data = nullptr;
    int dataSize = 0;
public:
    Graph();
    Graph(SDL_FPoint anchor, float width, float height);
    ~Graph();
    void changeDimension(float width, float height);
    void changeAnchor(SDL_FPoint anchor);
    void display(SDL_Renderer *renderer);
    void drawBorder(SDL_Renderer *renderer) const;
    void update(Sound & sound);
};

#endif
