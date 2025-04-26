#include "map.h"
#include "TextM.h"
#include "game.h"
#include <cstdio>
//map.cpp


const int TILE_SIZE = 32;
int level1[20][20] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

Map::Map() {
    wall = TextureManager::LoadTexture("img/wall.png");
    coinTexture = TextureManager::LoadTexture("img/coin.png");
    src = { 0, 0, TILE_SIZE, TILE_SIZE };
    dest = { 0, 0, TILE_SIZE, TILE_SIZE };

    initCoins();
}

int Map::demcoin() const {
	int count = 0;
	for (int row = 0; row < 20; ++row) {
		for (int col = 0; col < 20; ++col) {
			if (coins[row][col] == 1) {
				count++;
			}
		}
	}
	return count;
}
void Map::initCoins() {
    for (int row = 0; row < 20; ++row) {
        for (int col = 0; col < 20; ++col) {
          
            coins[row][col] = (level1[row][col] == 0) ? 1 : 0;
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

bool Map::collectCoinAt(int row, int col) {
    if (row < 0 || row >= 20 || col < 0 || col >= 20) {
        return false;
    }

    if (coins[col][row] == 1) {
        coins[col][row] = 0;
        return true;
    }
    return false;
}

int Map::getTileSize() const {
    return TILE_SIZE;
}
