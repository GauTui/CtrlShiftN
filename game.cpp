#include "Game.h"
#include "TextM.h"
#include "nhanvatchinh.h"
#include "map.h"
#include "giangvien.h"

int score;
Map* Gmap = nullptr;
SDL_Renderer* Game::renderer = nullptr;
Game::Game() : isRunning(false), window(nullptr), pacman(nullptr),font(nullptr) {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        if (TTF_Init() == -1) {
            SDL_Log("TTF_Init failed: %s", TTF_GetError());
            isRunning = false;
            return;
        }

        font = TTF_OpenFont("ttf//font.ttf", 24);
        if (!font) {
            SDL_Log("Failed to load font: %s", TTF_GetError());
            isRunning = false;
            return;
        }
        isRunning = true;
    }

    pacman = new Pacman("img/bg21.jpg", 1, 1);
    Gmap = new Map();
    Gmap->initCoins();

    enemies.push_back(new GiangVien("img/giangvien.jpg", 100, 100));
    enemies.push_back(new GiangVien("img/giangvien.jpg", 300, 200));
    enemies.push_back(new GiangVien("img/giangvien.jpg", 500, 300));
}
void Game::kiemtravacham() {
    SDL_Rect pacRect = pacman->getRect();
    for (auto enemy : enemies) {
        SDL_Rect enemyRect = enemy->getRect();
        if (SDL_HasIntersection(&pacRect, &enemyRect)) {
            isRunning = false;
            SDL_Log("Thua m? r?i, t??ng th? nào :))");
        }
    }
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
    for (auto enemy : enemies) {
        enemy->update();
    }

    kiemtravacham();
    int row = pacman->getY() / Gmap->getTileSize();
    int col = pacman->getX() / Gmap->getTileSize();

    if (Gmap->collectCoinAt(row, col)) {
        score += 10; 
    }
}
void Game::renderScore() {
    SDL_Color textColor = { 255, 255, 255 };

    std::ostringstream scoreStream;
    scoreStream << "Score: " << score;
    std::string scoreText = scoreStream.str();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = { 10, 10, textSurface->w, textSurface->h };

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Game::render() {
    SDL_RenderClear(renderer);
    Gmap->drawMap();
    for (auto enemy : enemies) {
        enemy->render(renderer);
    }
    pacman->render();
    renderScore();
    SDL_RenderPresent(renderer);

}

void Game::clean() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
