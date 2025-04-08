#include "ground.h"
#include "textureManager.h"

void Ground::create(const char* filePath, SDL_Renderer* renderer){
    texture = TextureManager::loadTexture(filePath, renderer);
}

void Ground::scroll(){
    scrollingOffset -= GAME_SPEED;
    if (scrollingOffset < 0) scrollingOffset += GROUND_WIDTH;
}

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = GROUND_WIDTH;
    rect.h = GROUND_HEIGHT;

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Ground::show(SDL_Renderer* renderer){    
    renderTexture(renderer, texture, scrollingOffset - GROUND_WIDTH, GROUND_Y_POS);
    renderTexture(renderer, texture, scrollingOffset, GROUND_Y_POS);
    renderTexture(renderer, texture, scrollingOffset + GROUND_WIDTH, GROUND_Y_POS);
}