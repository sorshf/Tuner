#include "Text.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <iostream>

Text::Text(TTF_TextEngine* engine, TTF_Font* font) {
    font_ = font;
    if (!font_) {
        std::cerr << "Font Load Error: " << SDL_GetError() << std::endl;
    }
    engine_ = engine;
}

Text::~Text() {

    if (text_) {
        TTF_DestroyText(text_);
        text_ = nullptr;
    }

}

void Text::update(const char* text, SDL_Color* color) {
    if (text_) {
        TTF_DestroyText(text_);
    }
    
    text_ = TTF_CreateText(engine_, font_, text, 0);
    if (!text_) {
        std::cerr << "Text Creation Error: " << SDL_GetError() << std::endl;
    }

    TTF_SetTextColor(text_, color->r, color->g, color->b, color->a);
}


void Text::display(float x, float y) {
    if (text_ != nullptr) {
        TTF_DrawRendererText(text_, x, y);
    }
}