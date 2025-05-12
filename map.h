#pragma once
#include <SDL.h>

//map.h

class Map {
public:
    Map();
    bool collectCoinAt(int x, int y);
    void drawMap();
	void initCoins();
    int getTileSize() const;
    int demcoin() const;
	void loadLevel(int level);
    bool isWall(int x, int y) const;

private:
    SDL_Rect src, dest;
    SDL_Texture* wall;
    SDL_Texture* coinTexture;
    SDL_Texture* background;
    static const int TILE_SIZE = 32;
    int map[20][20];
    int coins[20][20];
    

};
