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
int level2[20][20] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
    {1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1},
    {1,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1},
    {1,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1},
    {1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1},
    {1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1},
    {1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
    {1,0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
    {1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1},
    {1,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
    {1,0,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1},
    {1,0,1,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Map::Map() {
    wall = TextureManager::LoadTexture("map/wall.png");
    background = TextureManager::LoadTexture("img/bkg.jpg");
    coinTexture = TextureManager::LoadTexture("map/coin.png");
    src = { 0, 0, TILE_SIZE, TILE_SIZE };
    dest = { 0, 0, TILE_SIZE, TILE_SIZE };

    initCoins();
}
void Map::loadLevel(int level) {
    const int (*selectedMap)[20] = nullptr;

    if (level == 1) selectedMap = level1;
    else if (level == 2) selectedMap = level2;
    else return;

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            map[i][j] = selectedMap[i][j];
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
          
            coins[row][col] = (map[row][col] == 0) ? 1 : 0;
        }
    }
}

bool Map::isWall(int x, int y) const {
    if (x < 0 || x >= 20 || y < 0 || y >= 20) return true;
    return map[y][x] == 1;
}

void Map::drawMap() {
    SDL_Rect fullRect = { 0, 0, 640, 640 };
    SDL_RenderCopy(Game::renderer, background, NULL, &fullRect);

    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 20; col++) {
            int tileType = map[row][col];
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
