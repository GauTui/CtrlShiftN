#include "nhanvatchinh.h"
#include "TextM.h"
#include "game.h"
#include "map.h"

//nhanvatchinh.cpp
extern Map* Gmap;
const int TILE_SIZE = 32;
const int UETMAN_SPEED = 2;
extern int score;

SDL_Rect Pacman::getRect() const {
    return destRect;
}
bool dichuyen(int pixelX, int pixelY, int tileW, int tileH) {
    int leftTile = pixelX / TILE_SIZE;
    int rightTile = (pixelX + tileW - 1) / TILE_SIZE;
    int topTile = pixelY / TILE_SIZE;
    int bottomTile = (pixelY + tileH - 1) / TILE_SIZE;

    return !(Gmap->isWall(leftTile, topTile) ||
        Gmap->isWall(rightTile, topTile) ||
        Gmap->isWall(leftTile, bottomTile) ||
        Gmap->isWall(rightTile, bottomTile));
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
        switch (event.key.keysym.sym) {
        case SDLK_UP:    pendingDirection = UP;    break;
        case SDLK_DOWN:  pendingDirection = DOWN;  break;
        case SDLK_LEFT:  pendingDirection = LEFT;  break;
        case SDLK_RIGHT: pendingDirection = RIGHT; break;
        }
    }
}

void Pacman::update() {
    int dx = 0, dy = 0;
    int px = destRect.x;
    int py = destRect.y;

    if (px % TILE_SIZE == 0 && py % TILE_SIZE == 0) {
        int tileX = px / TILE_SIZE;
        int tileY = py / TILE_SIZE;

        if (pendingDirection != huong) {
            int testX = tileX;
            int testY = tileY;

            switch (pendingDirection) {
            case UP:    testY--; break;
            case DOWN:  testY++; break;
            case LEFT:  testX--; break;
            case RIGHT: testX++; break;
            default: break;
            }

            if (!Gmap->isWall(testX, testY)) {
                huong = pendingDirection;
            }
        }

        int nextX = tileX;
        int nextY = tileY;
        switch (huong) {
        case UP:    nextY--; break;
        case DOWN:  nextY++; break;
        case LEFT:  nextX--; break;
        case RIGHT: nextX++; break;
        default: break;
        }

        if (Gmap->isWall(nextX, nextY)) {
            return;
        }
    }

    switch (huong) {
    case UP:    dy = -UETMAN_SPEED; break;
    case DOWN:  dy = UETMAN_SPEED;  break;
    case LEFT:  dx = -UETMAN_SPEED; break;
    case RIGHT: dx = UETMAN_SPEED;  break;
    default: break;
    }

    destRect.x += dx;
    destRect.y += dy;

    tileX = destRect.x / TILE_SIZE;
    tileY = destRect.y / TILE_SIZE;
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
