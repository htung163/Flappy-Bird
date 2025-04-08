#ifndef GROUND_H
#define GROUND_H

#include <SDL.h>
#include "def.h"

struct Ground{
    SDL_Texture* texture;
    double scrollingOffset = 0;

    void create(const char* filePath, SDL_Renderer* renderer);
    void scroll();
    void show(SDL_Renderer* renderer);
};

#endif