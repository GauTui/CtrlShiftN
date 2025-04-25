// Game.h
#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "nhanvatchinh.h"
#include "Map.h"
#include <sstream>
#include <string>
#include"giangvien.h"
#include<vector.>

extern int score;
class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }

    static SDL_Renderer* renderer;

private:
    bool isRunning;
    bool GameOver = false;
	bool BanThang = false;
    SDL_Window* window;
    SDL_Texture* hinhGameOver = nullptr;
    SDL_Texture* hinhWin = nullptr;
    TTF_Font* font;
    Pacman* pacman;
    void renderScore();
    std::vector<GiangVien*> enemies;
    void kiemtravacham();
};
