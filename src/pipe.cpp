#include "pipe.h"
#include "textureManager.h"

void Pipe::setSrc(int w, int h, int x, int y){
    src.w = w;
    src.h = h;
    src.x = x;
    src.y = y;
}

void Pipe::setDest(int w, int h, int x, int y){
    topDest.w = w;
    topDest.h = h;
    topDest.x = x;
    topDest.y = y;

    botDest.w = w;
    botDest.h = 800 + 50 - (h + GAP_HEIGHT);
    botDest.x = x;
    botDest.y = h + GAP_HEIGHT;
}

void Pipe::create(const char* filePath, SDL_Renderer* renderer){
    texture = TextureManager::loadTexture(filePath, renderer);

    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    setSrc(width, height, 0, 0);
}

int Pipe::randomPipeHeight(int l, int r){
    l = max(l, 150);
    r = min(r, 450);
    return rand() % (r - l + 1) + l;
}

void Pipe::updatePipe(int preTopHeight){
    if (Xpos <= -PIPE_WIDTH){
        Xpos += SCREEN_WIDTH + PIPE_WIDTH;
        topHeight = randomPipeHeight(preTopHeight - 200, preTopHeight + 250);
    }

    Xpos -= GAME_SPEED;
    setDest(PIPE_WIDTH, topHeight, Xpos, 0);
}

void Pipe::show(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, texture, &src, &topDest);
    SDL_RenderCopyEx(renderer, texture, &src, &botDest, 0, nullptr, SDL_FLIP_VERTICAL);
}