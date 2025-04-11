#include "nhanvatchinh.h"
#include "TextM.h"
#include "game.h"

const int TILE_SIZE = 32;

Pacman::Pacman(const char* textureFile, int x, int y) : tileX(x), tileY(y) {
    texture = TextureManager::LoadTexture(textureFile);
    srcRect = { 0, 0, 32, 32 };
    destRect = { x * TILE_SIZE, y * TILE_SIZE, 32, 32 };
}

void Pacman::handleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:    tileY--; break;
        case SDLK_DOWN:  tileY++; break;
        case SDLK_LEFT:  tileX--; break;
        case SDLK_RIGHT: tileX++; break;
        }
    }
}

void Pacman::update() {
    destRect.x = tileX * TILE_SIZE;
    destRect.y = tileY * TILE_SIZE;
}

void Pacman::render() {
    SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}
