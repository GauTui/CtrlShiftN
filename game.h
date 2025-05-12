// Game.h
#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "nhanvatchinh.h"
#include "Map.h"
#include <sstream>
#include <string>
#include"honma.h"
#include<vector.>
#include<SDL_mixer.h>

enum tinhtranggame {
    tt,
    thang,
    thua,
    chosangman
};
extern tinhtranggame ttg;
extern int currentlv;
extern int score;

struct Button {
    SDL_Rect rect;
    SDL_Texture* texture;
};

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
    void thoatgame();
	void loadLevel(int level);
    
    static SDL_Renderer* renderer;
    tinhtranggame ttg = chosangman;
    void showMenu();

private:
    bool isRunning;
    bool GameOver = false;
	bool BanThang = false;
    SDL_Window* window;
    SDL_Texture* hinhGameOver = nullptr;
    SDL_Texture* hinhWin = nullptr;
	SDL_Texture* hinhNextLevel = nullptr;
    TTF_Font* font;
    Pacman* pacman;
    void renderScore();
    std::vector<GiangVien*> enemies;
    void kiemtravacham();
};
