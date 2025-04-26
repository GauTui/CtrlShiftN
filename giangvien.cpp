#include"giangvien.h"
#include "Game.h"
#include <SDL_image.h>

GiangVien::GiangVien(const std::string path, int x, int y) : huongchuyendong(0) {
	rect = { x, y, 32, 32 };
	loadTexture(path, Game::renderer);
	bossgame = IMG_LoadTexture(Game::renderer, "img/animationboss.png");
	frameWidth = 32;
	frameHeight = 32;
	currentFrame = 0;
	frameDelay = 10;
	frameTimer = 0;
}
void GiangVien::loadTexture(const std::string& path, SDL_Renderer* renderer) {
	texture = IMG_LoadTexture(renderer, path.c_str());
	if (!texture) {
		SDL_Log("Unable to load texture: %s", IMG_GetError());
	}
}
void GiangVien::update() {
	rect.x += (huongchuyendong == 0) ? 2 : -2;
	if (rect.x < 0 || rect.x + rect.w > 640) {
		huongchuyendong = 1 - huongchuyendong;
	}
	frameTimer++;
	if (frameTimer >= frameDelay) {
		currentFrame = (currentFrame + 1) % 4;
		frameTimer = 0;
	}

}
void GiangVien::render(SDL_Renderer* renderer) {
	SDL_Rect rect = {
	(currentFrame % 2) * frameWidth,
	(currentFrame / 2) * frameHeight,
	frameWidth,
	frameHeight
	};
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (huongchuyendong == 1) {
		flip = SDL_FLIP_HORIZONTAL;
	}

	SDL_RenderCopyEx(renderer, bossgame, &rect, &this->rect, 0.0, nullptr, flip);
}
SDL_Rect GiangVien::getRect() const {
	return rect;
}