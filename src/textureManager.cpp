#include "textureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* filePath, SDL_Renderer* renderer){
    SDL_Surface* surface = IMG_Load(filePath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    return texture;
}