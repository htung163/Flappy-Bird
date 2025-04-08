#ifndef BIRD_H
#define BIRD_H

#include <SDL.h>
#include "def.h"

struct Bird{
    SDL_Texture* texture;
    SDL_Rect src, dest;

    double Ypos;
    double isJumping;
    double acceleration;
    double jumpHeight;
    int frame;

    Bird(){}

    void setSrc(int w, int h, int x, int y);
    void setDest(int w, int h, int x, double y);
    void setDest(double y);
    void setNewBird();
    
    void create(const char* filePath, SDL_Renderer* renderer);

    void update();
    void fall();
    void jump();

    void show(SDL_Renderer* renderer);
};

#endif