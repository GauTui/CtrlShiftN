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
    animTexture = IMG_LoadTexture(Game::renderer, "img/animation.png");
    frameWidth = 32;
    frameHeight = 29;
    currentFrame = 0;
    frameDelay = 10;
    frameTimer = 0;
}

void Pacman::handleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        int nextTileX = tileX;
        int nextTileY = tileY;

        switch (event.key.keysym.sym) {
        case SDLK_UP:
            nextTileY--;
            huong = UP;
            break;
        case SDLK_DOWN:
            nextTileY++;
            huong = DOWN;
            break;
        case SDLK_LEFT:
            nextTileX--;
            huong = LEFT;
            break;
        case SDLK_RIGHT:
            nextTileX++;
            huong = RIGHT;
            break;
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
    frameTimer++;
    if (frameTimer >= frameDelay) {
        currentFrame = (currentFrame + 1) % 4;
        frameTimer = 0;
    }
}

void Pacman::render() {
   // SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
    SDL_Rect srcRect = {
    (currentFrame % 2) * frameWidth,
    (currentFrame / 2) * frameHeight,
    frameWidth,
    frameHeight
    };
    SDL_Rect destRect = getRect();
    double angle = 0.0;
    switch (huong) {
    case UP:    angle = 270.0; break;
    case DOWN:  angle = 90.0;  break;
    case LEFT:  angle = 180.0; break;
    case RIGHT: angle = 0.0;   break;
    }

    SDL_RenderCopyEx(Game::renderer, animTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
}
