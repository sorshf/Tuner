#include "Text.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <iostream>

Text::Text(SDL_Color color):
    m_color(color){}

Text::~Text() {

    if (m_text) {
        TTF_DestroyText(m_text);
        m_text = nullptr;
    }

}

void Text::update(const char* text, TTF_TextEngine* engine, TTF_Font* font) {
    if (m_text) {
        TTF_DestroyText(m_text);
    }
    
    m_text = TTF_CreateText(engine, font, text, 0);
    if (!m_text) {
        std::cerr << "Text Creation Error: " << SDL_GetError() << std::endl;
    }

    TTF_SetTextColor(m_text, m_color.r, m_color.g, m_color.b, m_color.a);
}


void Text::display(float x, float y) {
    if (m_text != nullptr) {
        TTF_DrawRendererText(m_text, x, y);
    }
}