#include "textObject.h"

using namespace std;

void textObject::update(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const char* text){
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (surface == nullptr){
        cerr << "Error: " << TTF_GetError() << endl;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == nullptr){
        cout << "Error: " << SDL_GetError() << endl;
    }
    
    SDL_FreeSurface(surface);
}

void textObject::setDest(int w, int h, int x, int y){
    dest.w = w;
    dest.h = h;
    dest.x = x;
    dest.y = y;
}

void textObject::show(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}