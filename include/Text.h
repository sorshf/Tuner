#ifndef Text_H
#define Text_H

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>

class Text {
    private:
        TTF_Font* font_ = nullptr;
        TTF_Text* text_ = nullptr;
        TTF_TextEngine* engine_ = nullptr;
    public:
        Text(TTF_TextEngine* engine, TTF_Font* font);
        ~Text();
        void update(const char* text, SDL_Color* color);
        void display(float x, float y);

};

#endif
