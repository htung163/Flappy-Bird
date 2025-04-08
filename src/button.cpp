#include "button.h"
#include "textureManager.h"

void Button::create(const char* filePath, SDL_Renderer* renderer){
    texture = TextureManager::loadTexture(filePath, renderer);
    
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    setSrc(width, height, 0, 0);
}

void Button::setSrc(int w, int h,int x, int y){
    src.w = w;
    src.h = h;
    src.x = x;
    src.y = y;
}

void Button::setDest(int w, int h, int x, int y){
    dest.w = w;
    dest.h = h;
    dest.x = x;
    dest.y = y;
}

void Button::show(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, texture, &src, &dest);
}