#include "map.h"
#include "TextM.h"
#include "game.h"

//map.cpp

const int TILE_SIZE = 32;

int coins[20][20];

int level1[20][20] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,1},
    {1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1},
    {1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


Map::Map() {
    wall = TextureManager::LoadTexture("img/sangphai.png");
    coinTexture = TextureManager::LoadTexture("img/4.jpg");
    src = { 0, 0, TILE_SIZE, TILE_SIZE };
    dest = { 0, 0, TILE_SIZE, TILE_SIZE };

    for (int row = 0; row < 20; ++row) {
        for (int col = 0; col < 20; ++col) {
            if (level1[row][col] == 0) { 
                coins[row][col] = 1;
            }
            else {
                coins[row][col] = 0; 
            }
        }
    }
}

bool isWall(int x, int y) {
    int col = x / TILE_SIZE;
    int row = y / TILE_SIZE;
    if (row < 0 || row >= 20 || col < 0 || col >= 20) {
        return true;
    }
    return level1[row][col] == 1;
}

void Map::drawMap() {
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 20; col++) {
            int tileType = level1[row][col];
            if (tileType == 1) {
                dest.x = col * TILE_SIZE;
                dest.y = row * TILE_SIZE;
                SDL_RenderCopy(Game::renderer, wall, &src, &dest);
            }
            if (coins[row][col] == 1) {
                dest.x = col * TILE_SIZE;
                dest.y = row * TILE_SIZE;
                SDL_RenderCopy(Game::renderer, coinTexture, &src, &dest);
            }
        }
    }
    
}
