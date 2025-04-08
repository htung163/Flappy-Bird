#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>

struct Background{
    SDL_Texture* texture;

    Background(){}

    void create(const char* filePath, SDL_Renderer* renderer);
    void show(SDL_Renderer* renderer);
};

#endif