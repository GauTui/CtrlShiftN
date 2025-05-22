// Game.h
#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "nhanvatchinh.h"
#include "Map.h"
#include <sstream>
#include <string>
#include"honma.h"
#include<vector>
#include<SDL_mixer.h>

enum tinhtranggame {
    tt,    //dangchoi
    thang,     // winchosangman
    thua,    //thuachuanbiquayvemenu
    chosangman,     //manhinhcho
    tamdung
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
    void startGame();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }
    void thoatgame();
	void loadLevel(int level);
    bool loadPauseMenuTextures();
    static SDL_Renderer* renderer;
    tinhtranggame ttg = chosangman;
    void showMenu();
    Mix_Music* menuMusic;
    Mix_Music* gameMusic;
    SDL_Texture* texLoaBat;
    SDL_Texture* texLoaTat;
    SDL_Rect loaRect;
    bool isSoundOn;
    bool isMuted = false;

private:
    bool isRunning;
    bool GameOver = false;
	bool BanThang = false;
    bool isOverlayVisible = false;

    SDL_Window* window;
    SDL_Texture* hinhGameOver = nullptr;
    SDL_Texture* hinhWin = nullptr;
	SDL_Texture* hinhNextLevel = nullptr;

	SDL_Texture* pauseTexture = nullptr;
    SDL_Texture* exitTexture = nullptr;
    SDL_Texture* resumeTexture = nullptr;
    SDL_Texture* restartTexture = nullptr;

    SDL_Texture* buttonTexture = nullptr;
    SDL_Texture* overlayTexture = nullptr;

    SDL_Texture* closeButtonTexture = nullptr;

    SDL_Rect buttonRect;
    SDL_Rect overlayRect;
	SDL_Rect pauseRect;

    SDL_Texture* quitBtnTex = nullptr;
    SDL_Rect pauseBgRect, resumeBtnRect, restartBtnRect, quitBtnRect;
    TTF_Font* font;
    SDL_Rect startRect;
    SDL_Rect quitRect;
    Pacman* pacman;
    void renderScore();
    std::vector<Ghost*> enemies;
    void kiemtravacham();
};
