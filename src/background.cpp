#include "background.h"
#include "textureManager.h"

void Background::create(const char* filePath, SDL_Renderer* renderer){
    texture = TextureManager::loadTexture(filePath, renderer);
}

void Background::show(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}