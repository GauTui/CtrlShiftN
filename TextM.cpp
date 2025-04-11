#include "TextM.h"
#include "Game.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}
