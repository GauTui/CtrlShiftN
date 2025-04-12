#pragma once
#include <SDL.h>

//map.h

bool isWall(int x, int y);

class Map {
public:
    Map();
    void drawMap();
private:
    SDL_Rect src, dest;
    SDL_Texture* wall;
    SDL_Texture* coinTexture;

};
