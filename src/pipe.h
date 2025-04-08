#ifndef PIPE_H
#define PIPE_H

#include <SDL.h>
#include <iostream>

struct Pipe{
    int Xpos;
    int topHeight;

    SDL_Texture *texture;
    SDL_Rect topDest, botDest;
    SDL_Rect src;

    Pipe(){};

    void setSrc(int w, int h, int x, int y);
    void setDest(int w, int h, int x, int y);

    void create(const char* filePath, SDL_Renderer* renderer);
    void updatePipe(int preTopHeight);
    int randomPipeHeight(int l, int r);
    void show(SDL_Renderer* renderer);
};

#endif