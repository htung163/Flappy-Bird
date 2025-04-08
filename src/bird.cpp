#include "bird.h"
#include "textureManager.h"

void Bird::setSrc(int w, int h, int x, int y){
    src.w = w;
    src.h = h;
    src.x = x;
    src.y = y;
}

void Bird::setDest(int w, int h, int x, double y){
    dest.w = w;
    dest.h = h;
    dest.x = x;
    dest.y = y;
}

void Bird::setDest(double y){
    dest.y = y;
}

void Bird::setNewBird(){
    Ypos = BIRD_Y_POS;
    isJumping = false;
    acceleration = GRAVITY;
    jumpHeight = JUMP_HEIGHT;
    frame = 0;
}

void Bird::create(const char* filePath, SDL_Renderer* renderer){
    texture = TextureManager::loadTexture(filePath, renderer);
    setSrc(BIRD_WIDTH, BIRD_HEIGHT, 0, 0);
    setDest(BIRD_WIDTH * 3, BIRD_HEIGHT * 3, BIRD_X_POS, BIRD_Y_POS);
    setNewBird();
}

void Bird::update(){
    frame++;
    frame %= 30;
    setSrc(BIRD_WIDTH, BIRD_HEIGHT, (frame / 10) * BIRD_WIDTH, 0);
}

void Bird::fall(){
    acceleration += 0.12;

    if (isJumping){
        jumpHeight += acceleration;
        Ypos += acceleration + jumpHeight;

        if (jumpHeight > 0){
            isJumping = false;
            jumpHeight = JUMP_HEIGHT;
        }
    }
    else{
        Ypos += acceleration;
    }
    
    Ypos = max(Ypos, 0.0);
    setDest(Ypos);
}

void Bird::jump(){
    isJumping = true;
    acceleration = GRAVITY;
}

void Bird::show(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, texture, &src, &dest);
}