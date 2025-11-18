#include "Graph.h"
#include <SDL3/SDL.h>
#include <iostream>
#include "Sound.h"
using namespace std;

float arrMax(float arr[], int size) {
    float max = arr[0];

    for (int i = 0; i < size; i++)
    {
        if (arr[i] > max) {
         max = arr[i];   
        }

    }

    return max;
    
}

float arrMin(float arr[], int size) {
    float min = arr[0];

    for (int i = 0; i < size; i++)
    {
        if (arr[i] < min) {
         min = arr[i];   
        }

    }

    return min;
}

Graph::Graph() {
    width_ = 100;
    height_ = 100;
    anchor_ = {0.0f, 0.0f};
}

Graph::Graph(SDL_FPoint anchor, float width, float height) {
    width_ = width;
    height_ = height;
    anchor_ = anchor;
}

Graph::~Graph() {
    if (data != nullptr) {
        delete [] data;
    }
}

void Graph::changeDimension(float width, float height) {
    width_ = width;
    height_ = height;
}

void Graph::changeAnchor(SDL_FPoint anchor) {
    anchor_ = anchor;
}

void Graph::drawBorder(SDL_Renderer *renderer) const {
    SDL_FPoint borders[] = {anchor_,        {anchor_.x+width_, anchor_.y},{anchor_.x+width_, anchor_.y+height_},
                            {anchor_.x, anchor_.y+height_}, anchor_};
    SDL_RenderLines(renderer, borders, 5);
}

void Graph::update(Sound & sound) {

    int soundSize = sound.getSize();
    float* soundData = sound.getData();

    //Create dynamic array if there isn't already one or the number of points change
    if (data == nullptr || dataSize != soundSize){
        data = new SDL_FPoint[soundSize];
        dataSize = soundSize;
    }

    //calculate min and max
    const float min = arrMin(soundData, soundSize);
    const float max = arrMax(soundData, soundSize);

    //populate the data with the adjusted points
    for (int i = 0; i < soundSize; i++) {
        float newY = (soundData[i] - min)/(max - min) * height_;
        newY = (anchor_.y + height_) - newY;

        float newX = (width_/soundSize * i) + anchor_.x;

        data[i] = {newX, newY};
    }

}

void Graph::display(SDL_Renderer *renderer) {
    if (dataSize != 0) {
        SDL_RenderLines(renderer, data, dataSize);
        drawBorder(renderer);
    } else {
        drawBorder(renderer);
    }

}