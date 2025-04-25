#pragma once
#include <SDL.h>

//map.h

bool isWall(int x, int y);

class Map {
public:
    Map();
    bool collectCoinAt(int x, int y);
    void drawMap();
	void initCoins();
    int getTileSize() const;
    int demcoin() const;

private:
    SDL_Rect src, dest;
    SDL_Texture* wall;
    SDL_Texture* coinTexture;
    static const int TILE_SIZE = 32;
    int coins[20][20];
    friend bool isWall(int x, int y);

};
