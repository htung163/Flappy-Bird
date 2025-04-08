#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "game.h"

class TextureManager{
public:
    static SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
};

#endif