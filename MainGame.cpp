#include "game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
    game = new Game();
    game->init("Lai Tuan Duc-24021414", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, false);

    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
        SDL_Delay(100);
    }

    game->clean();
    return 0;
}