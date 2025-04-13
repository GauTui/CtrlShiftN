#include "TextM.h"
#include "Game.h"

//textM.cpp

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
    SDL_Surface* tempSurface = IMG_Load(fileName);
    if (tempSurface == nullptr) {
     
        SDL_Log("Unable to load image %s! SDL_image Error: %s", fileName, IMG_GetError());
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if (tex == nullptr) {
   
        SDL_Log("Unable to create texture from %s! SDL_Error: %s", fileName, SDL_GetError());
    }

    SDL_FreeSurface(tempSurface);
    return tex;
}
