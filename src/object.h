#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>

struct Object{
    SDL_Texture* texture;
    SDL_Rect src, dest;

    Object(){}

    void create(const char* filePath, SDL_Renderer* renderer);
    void setSrc(int w, int h, int x, int y);
    void setDest(int w, int h, int x, int y);
    void show(SDL_Renderer* renderer);
};

#endif