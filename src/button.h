#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>

struct Button{
    SDL_Texture* texture;
    SDL_Rect src, dest;

    Button(){}

    void create(const char* filePath, SDL_Renderer* renderer);
    void setSrc(int w, int h, int x, int y);
    void setDest(int w, int h, int x, int y);
    void show(SDL_Renderer* renderer);
};

#endif