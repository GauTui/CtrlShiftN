#include "Game.h"
//main.cpp
Game* game = nullptr;

int main(int argc, char* argv[]) {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Lai Tuan Duc-24021414--UETman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, false);

    while (game->running()) {
        if (game->ttg == chosangman) {
            game->showMenu();
            if (!game->running()) break;
        }
        if (game->ttg == tt || game->ttg == tamdung) {
            frameStart = SDL_GetTicks();
            game->handleEvents();
            if (game->ttg == tt) {
                game->update();
            }
            game->render();
            frameTime = SDL_GetTicks() - frameStart;
            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
        if ((game->ttg == thang || game->ttg == thua) && game->running()) {
            game->thoatgame();
            if (!game->running()) break;
        }
    }
    game->clean();
    return 0;
}
