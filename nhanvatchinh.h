#pragma once
///nhanvatchinh.h
#include <SDL.h>

class Pacman {
public:
    Pacman(const char* textureFile, int tileX, int tileY);
    void handleInput(SDL_Event& event);
    void update();
    void render();
private:
    int tileX, tileY;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
};
