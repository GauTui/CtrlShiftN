#include"giangvien.h"
#include "Game.h"
#include <SDL_image.h>

GiangVien::GiangVien(const std::string path, int x, int y) : huong(0) {
	rect = { x, y, 32, 32 };
	loadTexture(path, Game::renderer);
}
void GiangVien::loadTexture(const std::string& path, SDL_Renderer* renderer) {
	texture = IMG_LoadTexture(renderer, path.c_str());
	if (!texture) {
		SDL_Log("Unable to load texture: %s", IMG_GetError());
	}
}
void GiangVien::update() {
	rect.x += (huong == 0) ? 2 : -2;
	if (rect.x < 0 || rect.x + rect.w > 640) {
		huong = 1 - huong;
	}
}
void GiangVien::render(SDL_Renderer* renderer) {
	if (texture) {
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}
}
SDL_Rect GiangVien::getRect() const {
	return rect;
}