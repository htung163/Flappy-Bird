#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

struct textObject{
    SDL_Texture* texture;
    SDL_Rect dest;

    void update(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const char* text);
    void setDest(int w, int h, int x, int y);
    void show(SDL_Renderer* renderer);
};


#endif