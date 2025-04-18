#pragma once
#include <SDL.h>
#include<string>

class GiangVien {
public:
	GiangVien(const std::string path, int x, int y);
	void update();
	void render(SDL_Renderer* renderer);
	SDL_Rect getRect() const;
private:
	SDL_Texture* texture;
	SDL_Rect rect;
	int huong;
	void loadTexture(const std::string& path, SDL_Renderer* renderer);
};