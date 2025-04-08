#include "game.h"

using namespace std;

Game::Game(){
    score = 0;
    isPlaying = isDead = false;

    window = nullptr;
    renderer = nullptr;
}

int scoreWidth(int score){
    if (score == 0) return SCORE_WIDTH;

    int cnt = 0;
    while (score > 0){
        cnt ++;
        score /= 10;
    }

    return cnt * SCORE_WIDTH;
}

void Game::init(){
    srand(time(nullptr));

    // sdl
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        return void(cerr << "Error: " << SDL_GetError() << endl);
    }

    // sdl_image
    renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        return void(cerr << "Error: " << SDL_GetError() << endl);
    }

    // mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        return void(cerr << "Error: " << Mix_GetError() << endl);
    }
    else{
        jumpSound = Mix_LoadWAV(JUMP_SOUND);
        hitSound = Mix_LoadWAV(HIT_SOUND);
        pointSound = Mix_LoadWAV(POINT_SOUND);
        fallSound = Mix_LoadWAV(FALL_SOUND);
        mouseClick = Mix_LoadWAV(MOUSE_CLICK);
        music = Mix_LoadMUS(MUSIC);
    }

    // ttf
    if (TTF_Init() < 0){
        return void(cerr << "Error: " << TTF_GetError() << endl);
    }
    else{
        font = TTF_OpenFont(FONT, SCORE_SIZE);

        introText.update(renderer, font, red, "FLAPPY BIRD");
        introText.setDest(600, 150, 200, 150);

        lostText.update(renderer, font, red, "You Lose!");
        lostText.setDest(600, 150, 200, 150);

        highScoreText.update(renderer, font, red, "High Score: ");
        highScoreText.setDest(200, SCORE_HEIGHT, 20, 20);

        scoreText.update(renderer, font, black, "Score: ");
        scoreText.setDest(150, SCORE_HEIGHT, 20, 80);
    }

    background.create(BACKGROUND, renderer);
    bird.create(BIRDS, renderer);
    ground.create(GROUND, renderer);
    
    // pipe
    for (int i = 0; i < PIPE_NUMBER; i++){
        pipe[i].create(PIPE, renderer);
        pipe[i].Xpos = SCREEN_WIDTH + PIPE_GAP * i;
        if (i == 0){
            pipe[i].topHeight = pipe[i].randomPipeHeight(150, 450);
        }
        else{
            int pre = (i - 1 + PIPE_NUMBER) % PIPE_NUMBER;
            pipe[i].topHeight = pipe[i].randomPipeHeight(pipe[pre].topHeight - 200, pipe[pre].topHeight + 250);
        }
    }

    // button
    buttons[PLAY].create(PLAY_BUTTON, renderer);
    buttons[PLAY].setSrc(49, 21, 0, 0);
    buttons[PLAY].setDest(200, 100, 400, 400);
    
    buttons[EXIT].create(EXIT_BUTTON, renderer);
    buttons[EXIT].setSrc(49, 21, 0, 0);
    buttons[EXIT].setDest(200, 100, 400, 550);
    
    buttons[REPLAY].create(REPLAY_BUTTON, renderer);
    buttons[REPLAY].setSrc(49, 21, 0, 0);
    buttons[REPLAY].setDest(200, 100, 400, 400);

    buttons[QUIT].create(EXIT_BUTTON, renderer);
    buttons[QUIT].setSrc(49, 21, 0, 0);
    buttons[QUIT].setDest(200, 100, 400, 550);
}

void Game::setNewGame(){
    score = 0;
    isPlaying = true;
    isDead = false;

    bird.create(BIRDS, renderer);

    for (int i = 0; i < PIPE_NUMBER; i++){
        pipe[i].Xpos = SCREEN_WIDTH + PIPE_GAP * i;
        pipe[i].topHeight = pipe[i].randomPipeHeight(150, 450);
    }
}

void Game::playSound(Mix_Chunk* sound){
    Mix_PlayChannel(-1, sound, 0);
}

void Game::event(){
    SDL_PollEvent(&e);
    switch (e.type){
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
            if (isPlaying && !isDead){
                if (e.key.keysym.sym == SDLK_SPACE){
                    if (!bird.isJumping){
                        bird.jump();
                        playSound(jumpSound);
                    }
                    else bird.fall();
                }
            }
            break;
            
        
        case SDL_MOUSEBUTTONDOWN:
            if (!isPlaying){
                if (insideObject(buttons[PLAY])){
                    playSound(mouseClick);
                    isPlaying = true;
                }
                else if (insideObject(buttons[EXIT])){
                    playSound(mouseClick);
                    exit(0);
                }
            }
            else{
                if (isDead){
                    if (insideObject(buttons[REPLAY])){
                        playSound(mouseClick);
                        setNewGame();
                    }
                    else if (insideObject(buttons[QUIT])){
                        playSound(mouseClick);
                        exit(0);
                    }
                }
            }
            break;
    }
}

void Game::update(){
    // music
    if (Mix_PlayingMusic() == 0){
        Mix_PlayMusic(music, -1);
    }
    else if (Mix_PausedMusic()){
        Mix_ResumeMusic();
    }

    // button
    for (int i = 0; i < 4; i++){
        if (insideObject(buttons[i])){
            buttons[i].setSrc(49, 21, 49, 0);
        }
        else{
            buttons[i].setSrc(49, 21, 0, 0);
        }
    }

    if (isPlaying && !isDead){
        // bird
        bird.fall();
        bird.update();

        // pipe
        for (int i = 0; i < PIPE_NUMBER; i++){
            int pre = (i - 1 +PIPE_NUMBER) % PIPE_NUMBER;
            pipe[i].updatePipe(pipe[pre].topHeight);
        }

        ground.scroll();

        // check collision
        isDead = detectCollision();
        if (isDead){
            playSound(hitSound);
            SDL_Delay(250);
            playSound(fallSound);
            SDL_Delay(500);
            return;
        }

        // update score
        for (int i = 0; i < PIPE_NUMBER; i++){
            if (pipe[i].Xpos + PIPE_WIDTH / 2 <= bird.dest.x && bird.dest.x <= pipe[i].Xpos + PIPE_WIDTH / 2 + 2){
                playSound(pointSound);
                score++;
                scoreNumber.update(renderer, font, black, to_string(score).c_str());
            }
        }
    }
}

void Game::show(){
    SDL_RenderClear(renderer);

    background.show(renderer);

    if (!isPlaying){
        introText.show(renderer);

        buttons[PLAY].show(renderer);
        buttons[EXIT].show(renderer);
    }
    else{
        if (isDead){
            lostText.show(renderer);

            buttons[REPLAY].show(renderer);
            buttons[QUIT].show(renderer);
        }
        else{
            bird.show(renderer);

            for (int i = 0; i < PIPE_NUMBER; i++){
                pipe[i].show(renderer);
            }
        }

        int best;

        ifstream fi("best.txt");
        fi >> best;
        best = max(best, score);
        fi.close();

        ofstream fo("best.txt");
        fo << best;
        fo.close();

        // high score
        highScoreNumber.update(renderer, font, red, to_string(best).c_str());
        highScoreNumber.setDest(scoreWidth(best), SCORE_HEIGHT, 220, 20);

        highScoreText.show(renderer);
        highScoreNumber.show(renderer);

        // score
        scoreNumber.update(renderer, font, black, to_string(score).c_str());
        scoreNumber.setDest(scoreWidth(score), SCORE_HEIGHT, 170, 80);

        scoreText.show(renderer);
        scoreNumber.show(renderer);
    }

    ground.show(renderer);

    SDL_RenderPresent(renderer);
}

bool Game::detectCollision(){
    SDL_Rect Bird = bird.dest;
    int birdX1 = Bird.x;
    double birdY1 = Bird.y + 13;
    int birdX2 = Bird.x + Bird.w - 10;
    double birdY2 = Bird.y + Bird.h - 3;

    if (birdY2 >= GROUND_Y_POS) return true;

    for (int i = 0; i < PIPE_NUMBER; i++){
        // check collision with top pipe
        SDL_Rect Pipe = pipe[i].topDest;
        int x1 = Pipe.x;
        int y1 = Pipe.y;
        int x2 = Pipe.x + Pipe.w;
        int y2 = Pipe.y + Pipe.h;

        if (x1 <= birdX2 && birdX2 <= x2 && birdY1 <= y2) return true;

        // check collision with bot pipe
        Pipe = pipe[i].botDest;
        x1 = Pipe.x;
        y1 = Pipe.y;
        x2 = Pipe.x + Pipe.w;
        y2 = Pipe.y + Pipe.h;

        if (x1 <= birdX2 && birdX2 <= x2 && birdY2 >= y1) return true;
    }
    
    return false;
}

bool Game::insideObject(Button button){
    int x, y;
    SDL_GetMouseState(&x, &y);

    SDL_Rect rect = button.dest;
    int x1 = rect.x;
    int y1 = rect.y;
    int x2 = rect.x + rect.w;
    int y2 = rect.y + rect.h;

    return (x1 <= x && x <= x2 && y1 <= y && y <= y2);
}

void Game::quit(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
}