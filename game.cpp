#include "Game.h"
#include "TextM.h"
#include "nhanvatchinh.h"
#include "map.h"

int score = 0;
Map* Gmap = nullptr;
SDL_Renderer* Game::renderer = nullptr;
Game::Game() : isRunning(false), window(nullptr), pacman(nullptr), Gmap(nullptr) {}
Game::~Game() {}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        isRunning = true;
    }

    pacman = new Pacman("img/bg2.png", 1, 1);
    Gmap = new Map();
    Gmap->initCoins();
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        isRunning = false;
    }
    pacman->handleInput(event);
}

void Game::update() {
    pacman->update();

    //int pacX = pacman->getX() / Gmap->getTileSize();
    //int pacY = pacman->getY() / Gmap->getTileSize();

    //if (Gmap->collectCoinAt(pacY, pacX)) {
        //score += 10; 
    //}
}


void Game::render() {
    SDL_RenderClear(renderer);
    Gmap->drawMap();
    pacman->render();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
