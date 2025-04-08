#include "game.h"

int main(int argc, char* argv[]){
    Game game;
    game.init();

    while (true){
        game.event();
        game.update();
        game.show();
    }

    game.quit();

    return 0;
}
