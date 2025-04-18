#include "nhanvatchinh.h"
#include "TextM.h"
#include "game.h"
#include "map.h"

//nhanvatchinh.cpp
extern Map* Gmap;
const int TILE_SIZE = 32;
extern int score;

SDL_Rect Pacman::getRect() const {
    return destRect;
}
bool dichuyen(int tileX, int tileY, int tileW, int tileH) {
    return !(
        isWall(tileX, tileY) ||
        isWall(tileX + tileW - 1, tileY) ||
        isWall(tileX, tileY + tileH - 1) ||
        isWall(tileX + tileW - 1, tileY + tileH - 1)
        );
}

Pacman::Pacman(const char* textureFile, int x, int y) : tileX(x), tileY(y) {
    texture = TextureManager::LoadTexture(textureFile);
    srcRect = { 0, 0, 32, 32 };
    destRect = { x * TILE_SIZE, y * TILE_SIZE, 32, 32 };
}

void Pacman::handleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        int nextTileX = tileX;
        int nextTileY = tileY;

        switch (event.key.keysym.sym) {
        case SDLK_UP:    nextTileY--; break;
        case SDLK_DOWN:  nextTileY++; break;
        case SDLK_LEFT:  nextTileX--; break;
        case SDLK_RIGHT: nextTileX++; break;
        }

        int pixelX = nextTileX * TILE_SIZE;
        int pixelY = nextTileY * TILE_SIZE;
        

        if (nextTileX >= 0 && nextTileX < 20 && nextTileY >= 0 && nextTileY < 20) {
            if (dichuyen(pixelX, pixelY, 32, 32)) {
                tileX = nextTileX;
                tileY = nextTileY;
            }
        }
    }
}

void Pacman::update() {
    destRect.x = tileX * TILE_SIZE;
    destRect.y = tileY * TILE_SIZE;
    if (Gmap->collectCoinAt(tileX, tileY)) {
        score += 10;
    }
}

void Pacman::render() {
    SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}
