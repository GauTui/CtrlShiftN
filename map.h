#pragma once
#include <SDL.h>
#include "TextM.h"

class Map {
public:
    Map(SDL_Renderer* ren);
    void DrawMap();

private:
    SDL_Rect src, dest;
    SDL_Texture* wall;
    SDL_Texture* coin;
    SDL_Renderer* renderer;

    const static int tileSize = 32;
    const static int rows = 20;
    const static int cols = 20;

    int map[rows][cols] = {
        // 0: tr?ng, 1: t??ng, 2: coin
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2,0,2,1},
        {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1},
        {1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1},
        {1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1},
        {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1},
        {1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
};
