#pragma once
#include <SDL.h>
#include<string>

class Ghost {
public:
	Ghost(const std::string path, int x, int y);
	void update();
	void render(SDL_Renderer* renderer);
	SDL_Rect getRect() const;
private:
	enum huongboss {
		LEFT2,
		RIGHT2
	};
	int frameWidth, frameHeight;
	int currentFrame;
	int frameDelay;
	int frameTimer;
	SDL_Texture* bossgame;
	SDL_Texture* texture;
	SDL_Rect rect;
	huongboss huong2;
	int huongchuyendong = RIGHT2;
	void loadTexture(const std::string& path, SDL_Renderer* renderer);
};