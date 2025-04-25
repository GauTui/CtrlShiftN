#pragma once
///nhanvatchinh.h
#include <SDL.h>
#include"giangvien.h"

class Pacman {
public:
    Pacman(const char* textureFile, int tileX, int tileY);
    void handleInput(SDL_Event& event);
    void update();
    void render();
    int getX() const { return x; }
    int getY() const { return y; }
    SDL_Rect getRect() const;

private:
    int frameWidth, frameHeight;
    int currentFrame;
    int frameDelay;
    int frameTimer;
    SDL_Texture* animTexture;
    int x, y;
    int tileX, tileY;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
};
