#include "map.h"

Map::Map(SDL_Renderer* ren) : renderer(ren) {
    wall = TextureManager::LoadTexture("assets/wall.png", ren);
    coin = TextureManager::LoadTexture("assets/coin.png", ren);

    src = { 0, 0, 32, 32 };
    dest = { 0, 0, 32, 32 };
}

void Map::DrawMap() {
    for (int row = 0; row < 11; row++) {
        for (int col = 0; col < 20; col++) {
            dest.x = col * 32;
            dest.y = row * 32;

            switch (map[row][col]) {
            case 1:
                SDL_RenderCopy(renderer, wall, &src, &dest);
                break;
            case 2:
                SDL_RenderCopy(renderer, coin, &src, &dest);
                break;
            default:
                break;
            }
        }
    }
}
