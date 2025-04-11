#pragma once
#include <SDL.h>

class Map {
public:
    Map();
    void drawMap();

private:
    SDL_Rect src, dest;
    SDL_Texture* wall;
};
