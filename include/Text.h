#ifndef Text_H
#define Text_H

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>

class Text {
    private:
        TTF_Text* m_text = nullptr;
        SDL_Color m_color;
    public:
        Text(SDL_Color color);
        ~Text();
        void update(const char* text, TTF_TextEngine* engine, TTF_Font* font);
        void display(float x, float y);

};

#endif
