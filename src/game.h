#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "def.h"
#include "textureManager.h"
#include "textObject.h"
#include "background.h"
#include "bird.h"
#include "ground.h"
#include "pipe.h"
#include "button.h"
#include "object.h"

using namespace std;

class Game{
private:
    int score;
    bool isPlaying;
    bool isDead;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;

    Mix_Chunk *jumpSound, *hitSound, *pointSound, *fallSound, *mouseClick;
    Mix_Music* music;

    TTF_Font* font;
    SDL_Color black = BLACK;
    SDL_Color red = RED;

    Background background;
    Bird bird;
    Ground ground;
    Pipe pipe[PIPE_NUMBER];
    textObject introText, lostText;
    textObject scoreText, scoreNumber;
    textObject highScoreText, highScoreNumber;
    
    Button buttons[4];
    enum{
        PLAY,
        EXIT,
        REPLAY,
        QUIT
    };

public:
    Game();
    void init();
    void setNewGame();
    void event();
    void update();
    void show();
    void playSound(Mix_Chunk* sound);
    bool detectCollision();
    bool insideObject(Button button);
    void quit();
};

#endif