#include "Game.h"
#include "TextM.h"
#include "nhanvatchinh.h"
#include "map.h"
#include "honma.h"
#include<iostream>

int score;
int currentlv = 1;
tinhtranggame ttg = tt;

Map* Gmap = nullptr;
SDL_Renderer* Game::renderer = nullptr;
Game::Game() : isRunning(false), window(nullptr), pacman(nullptr), font(nullptr) {}
Game::~Game() {}
bool isStartHovered = false;
bool isQuitHovered = false;
bool isSoundHovered = false;
bool isPauseHovered = false;
bool isHuongdanHovered = false;

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        if (TTF_Init() == -1) {
            SDL_Log("TTF_Init failed: %s", TTF_GetError());
            isRunning = false;
            return;
        }

        font = TTF_OpenFont("ttf//font.ttf", 24);
        if (!font) {
            SDL_Log("Failed to load font: %s", TTF_GetError());
            isRunning = false;
            return;
        }
        isRunning = true;
    }
    if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)) == 0) {
        SDL_Log("IMG_Init failed: %s", IMG_GetError());
        isRunning = false;
        return;
    }
    resumeTexture = IMG_LoadTexture(renderer, "img/resume.png");
    restartTexture = IMG_LoadTexture(renderer, "img/restart.png");
    exitTexture = IMG_LoadTexture(renderer, "img/exit.png");
    pauseTexture = IMG_LoadTexture(renderer, "img/pause.png");

    texLoaBat = IMG_LoadTexture(renderer, "img/volume_on.png");
    texLoaTat = IMG_LoadTexture(renderer, "img/volume_off.png");
    loaRect = { 555, 10, 70, 70 };
	
	pauseRect = { 640 - 170, 10, 70, 70 };
    isSoundOn = true;
    buttonTexture = IMG_LoadTexture(renderer, "img/huongdan.png");
    if (!buttonTexture) {
        SDL_Log("Failed to load huongdan.jpg: %s", IMG_GetError());
    }
    overlayTexture = IMG_LoadTexture(renderer, "img/overlay.png");
    if (!overlayTexture) {
        SDL_Log("Failed to load overlay.jpg: %s", IMG_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
        isRunning = false;
        return;
    }
    menuMusic = Mix_LoadMUS("sound/menu.mp3");
    if (!menuMusic) {
        SDL_Log("Failed to load menu music: %s", Mix_GetError());
    }
	gameMusic = Mix_LoadMUS("sound/game.mp3");
	if (!gameMusic) {
		SDL_Log("Failed to load game music: %s", Mix_GetError());
	}
    else if (isSoundOn) {
        Mix_PlayMusic(gameMusic, -1);
    }
    Mix_PlayMusic(menuMusic, -1);
    hinhGameOver = IMG_LoadTexture(renderer, "img/gameover.png");
    hinhWin = IMG_LoadTexture(renderer, "img/win.png");
    hinhNextLevel = IMG_LoadTexture(renderer, "img/sangman.png");
    if (!hinhGameOver) {
        SDL_Log("Failed to load game over image: %s", IMG_GetError());
        isRunning = false;
        return;
    }
    Gmap = new Map();
    Gmap->initCoins();
    loadLevel(currentlv);
}
void Game::loadLevel(int level) {
    score = 0;
    delete pacman;
    for (auto enemy : enemies) delete enemy;
    enemies.clear();
    Gmap->loadLevel(level);
    Gmap->initCoins();
    pacman = new Pacman("img/animation.png", 1, 1);

    if (level == 1) {

        //enemies.push_back(new Ghost("img/animationboss.png", 150, 96));
        //enemies.push_back(new Ghost("img/animationboss.png", 350, 544));
        enemies.push_back(new Ghost("img/animationboss.png", 200, 288));
        //enemies.push_back(new Ghost("img/animationboss.png", 250, 480));
        enemies.push_back(new Ghost("img/animationboss.png", 100, 32));

    }
    else if (level == 2) {

        enemies.push_back(new Ghost("img/animationboss.png", 200, 96));
       // enemies.push_back(new Ghost("img/animationboss.png", 250, 224));
        //enemies.push_back(new Ghost("img/animationboss.png", 300, 288));
        enemies.push_back(new Ghost("img/animationboss.png", 360, 416));
        //enemies.push_back(new Ghost("img/animationboss.png", 412, 480));
        enemies.push_back(new Ghost("img/animationboss.png", 125, 544));

    }
    else {
        isRunning = false;
    }
}
void Game::kiemtravacham() {
    SDL_Rect pacRect = pacman->getRect();
    for (auto enemy : enemies) {
        SDL_Rect enemyRect = enemy->getRect();
        if (SDL_HasIntersection(&pacRect, &enemyRect)) {
            ttg = thua;
            GameOver = true;
            return;
        }
    }
}
void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        isRunning = false;
        return;
    }
    if (ttg == thua || ttg == thang) {
        if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN) {
            if (ttg == thang && currentlv == 1) {
                currentlv++;
                loadLevel(currentlv);
                ttg = tt;
                BanThang = false;
            }
            if (ttg == thua) {
                ttg = chosangman;
            }
        }
        return;
    }
    if (ttg == tamdung) {
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;
            SDL_Point mousePoint = { x, y };

            SDL_Rect resumeRect = { 640 / 2 - 75, 200, 150, 50 };
            SDL_Rect restartRect = { 640 / 2 - 75, 270, 150, 50 };
            SDL_Rect exitRect = { 640 / 2 - 75, 340, 150, 50 };

            if (SDL_PointInRect(&mousePoint, &resumeRect)) {
                ttg = tt;
            }
            else if (SDL_PointInRect(&mousePoint, &restartRect)) {
                loadLevel(currentlv);
                ttg = tt;
            }
            else if (SDL_PointInRect(&mousePoint, &exitRect)) {
                ttg = chosangman;
            }
        }
        return;
    }
    if (ttg == tt && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        SDL_Point mousePoint = { mouseX, mouseY };

        SDL_Rect settingsButtonRect = { 640 - 170, 10, 70, 70 };
        if (SDL_PointInRect(&mousePoint, &settingsButtonRect)) {
            ttg = tamdung;
            return;
        }
    }
    if (event.type == SDL_MOUSEMOTION) {
        int x = event.motion.x;
        int y = event.motion.y;

        isStartHovered = (x >= startRect.x && x <= startRect.x + startRect.w &&
            y >= startRect.y && y <= startRect.y + startRect.h);
        isQuitHovered = (x >= quitRect.x && x <= quitRect.x + quitRect.w &&
            y >= quitRect.y && y <= quitRect.y + quitRect.h);
        isSoundHovered = (x >= loaRect.x && x <= loaRect.x + loaRect.w &&
            y >= loaRect.y && y <= loaRect.y + loaRect.h);
        isHuongdanHovered = (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
            y >= buttonRect.y && y <= buttonRect.y + buttonRect.h);
    }
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        int x = event.button.x;
        int y = event.button.y;

        if (isStartHovered) {
            startGame();
        }
        if (x >= loaRect.x && x <= loaRect.x + loaRect.w &&
            y >= loaRect.y && y <= loaRect.y + loaRect.h) {
            isSoundOn = !isSoundOn;
            if (isSoundOn)
                Mix_ResumeMusic();
            else
                Mix_PauseMusic();
        }
        else if (isQuitHovered) {
            isRunning = false;
        }
    }
    pacman->handleInput(event);
}
void Game::update() {
    if (ttg == thua || ttg == thang || GameOver) {
        return;
    }
    pacman->update();
    for (auto enemy : enemies) {
        enemy->update();
    }
    kiemtravacham();
    int row = pacman->getY() / Gmap->getTileSize();
    int col = pacman->getX() / Gmap->getTileSize();

    if (Gmap->collectCoinAt(row, col)) {
        score += 10;
    }
    if (Gmap->demcoin() == 0) {
        ttg = thang;
        BanThang = true;
        Mix_HaltMusic();
    }
}
void Game::renderScore() {
    SDL_Color textColor = { 255, 255, 255 };

    std::ostringstream scoreStream;
    scoreStream << "Score: " << score;
    std::string scoreText = scoreStream.str();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = { 10, 10, textSurface->w, textSurface->h };

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
void Game::startGame() {
    Mix_HaltMusic();
	Mix_PlayMusic(gameMusic, -1);
    isRunning = true;
    GameOver = false;
    BanThang = false;
    score = 0;
    currentlv = 1;
    ttg = tt;
}
void Game::showMenu() {
    SDL_Event e;
    bool inMenu = true;

    SDL_Surface* bgSurface = IMG_Load("img/background.jpg");
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    SDL_Surface* startSurface = IMG_Load("img/start.png");
    SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startSurface);
    SDL_FreeSurface(startSurface);
    SDL_Rect startRect = { 200, 300, 240, 80 };

    SDL_Surface* quitSurface = IMG_Load("img/exit.png");
    SDL_Texture* quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);
    SDL_FreeSurface(quitSurface);
    SDL_Rect quitRect = { 200, 420, 240, 80 };

    SDL_Rect buttonRect = { 550, 500, 80, 80 };
    SDL_Rect overlayRect = { 20, 70, 600, 400 };


    bool isStartHovered = false;
    bool isQuitHovered = false;

    Mix_HaltMusic();
    Mix_PlayMusic(menuMusic, -1);

    while (inMenu) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                ttg = thua;
                inMenu = false;
            }
            else if (e.type == SDL_MOUSEMOTION) {
                int x = e.motion.x;
                int y = e.motion.y;
                isStartHovered = (x >= startRect.x && x <= startRect.x + startRect.w &&
                    y >= startRect.y && y <= startRect.y + startRect.h);
                isQuitHovered = (x >= quitRect.x && x <= quitRect.x + quitRect.w &&
                    y >= quitRect.y && y <= quitRect.y + quitRect.h);
                isSoundHovered = (x >= loaRect.x && x <= loaRect.x + loaRect.w &&
                    y >= loaRect.y && y <= loaRect.y + loaRect.h);
                isPauseHovered = (x >= pauseRect.x && x <= pauseRect.x + pauseRect.w &&
                    y >= pauseRect.y && y <= pauseRect.y + pauseRect.h);
                isHuongdanHovered = (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
                    y >= buttonRect.y && y <= buttonRect.y + buttonRect.h);
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                if (x >= loaRect.x && x <= loaRect.x + loaRect.w &&
                    y >= loaRect.y && y <= loaRect.y + loaRect.h) {
                    isSoundOn = !isSoundOn;
                    if (isSoundOn)
                        Mix_ResumeMusic();
                    else
                        Mix_PauseMusic();
                }

                if (x >= startRect.x && x <= startRect.x + startRect.w &&
                    y >= startRect.y && y <= startRect.y + startRect.h) {
                    Mix_HaltMusic();
                    inMenu = false;
                    startGame();
                }
                else if (x >= quitRect.x && x <= quitRect.x + quitRect.w &&
                    y >= quitRect.y && y <= quitRect.y + quitRect.h) {
                    ttg = thua;
                    inMenu = false;
                    isRunning = false;
                }
                else if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
                    y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
                    isOverlayVisible = !isOverlayVisible;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
        SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
        SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);

        if (isStartHovered) {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
            SDL_Rect overlay = startRect;
            SDL_RenderFillRect(renderer, &overlay);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        }

        if (isQuitHovered) {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
            SDL_Rect overlay = quitRect;
            SDL_RenderFillRect(renderer, &overlay);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        }
        if (isSoundHovered) {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
            SDL_Rect overlay = loaRect;
            SDL_RenderFillRect(renderer, &overlay);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        }
        if (isHuongdanHovered) {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
            SDL_Rect overlay = buttonRect;
            SDL_RenderFillRect(renderer, &overlay);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        }
        if (isSoundOn)
            SDL_RenderCopy(renderer, texLoaBat, nullptr, &loaRect);
        else
            SDL_RenderCopy(renderer, texLoaTat, nullptr, &loaRect);
        SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);

        if (isOverlayVisible) {
            SDL_RenderCopy(renderer, overlayTexture, NULL, &overlayRect);
        }
        if (ttg == tt) {
            SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(bgTexture);
    SDL_DestroyTexture(startTexture);
    SDL_DestroyTexture(quitTexture);
}
void Game::render() {
    SDL_RenderClear(renderer);
    Gmap->drawMap();
    for (auto enemy : enemies) {
        enemy->render(renderer);
    }
    pacman->render();
    renderScore();
    if (GameOver) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
        SDL_Rect overlay = { 0, 0, 640, 640 };
        SDL_RenderFillRect(renderer, &overlay);
        SDL_Rect dstRect = { (640 - 400) / 2, (640 - 200) / 2, 400, 200 };
        SDL_RenderCopy(renderer, hinhGameOver, NULL, &dstRect);
        SDL_Rect quitRect = { 200, 450, 240, 80 };
        SDL_Surface* quitSurface = IMG_Load("img/exit.png");
        SDL_Texture* quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);
        SDL_FreeSurface(quitSurface);
        SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);
        SDL_DestroyTexture(quitTexture);
    }
    if (BanThang) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
        SDL_Rect overlay = { 0, 0, 640, 640 };
        SDL_RenderFillRect(renderer, &overlay);
        SDL_Rect dstRect = { (640 - 400) / 2, (640 - 200) / 2, 400, 200 };
        if (currentlv == 1) {
            SDL_RenderCopy(renderer, hinhNextLevel, NULL, &dstRect);
            SDL_Rect continueRect = { 200, 350, 240, 80 };
            SDL_Surface* continueSurface = IMG_Load("img/continue.png");
            SDL_Texture* continueTexture = SDL_CreateTextureFromSurface(renderer, continueSurface);
            SDL_FreeSurface(continueSurface);
            SDL_RenderCopy(renderer, continueTexture, NULL, &continueRect);
            SDL_DestroyTexture(continueTexture);
        }
        else if (currentlv == 2) {
            SDL_RenderCopy(renderer, hinhWin, NULL, &dstRect);
        }
        SDL_Rect quitRect = { 200, 450, 240, 80 };
        SDL_Surface* quitSurface = IMG_Load("img/exit.png");
        SDL_Texture* quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);
        SDL_FreeSurface(quitSurface);
        SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);
        SDL_DestroyTexture(quitTexture);
        SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
        if (isOverlayVisible) {
            SDL_RenderCopy(renderer, overlayTexture, NULL, &overlayRect);
        }
    }
    if (ttg == tamdung) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
        SDL_Rect overlay = { 0, 0, 640, 640 };
        SDL_RenderFillRect(renderer, &overlay);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

        SDL_Rect resumeRect = { 640 / 2 - 75, 200, 150, 50 };
        SDL_Rect restartRect = { 640 / 2 - 75, 270, 150, 50 };
        SDL_Rect exitRect = { 640 / 2 - 75, 340, 150, 50 };

        SDL_RenderCopy(renderer, resumeTexture, NULL, &resumeRect);
        SDL_RenderCopy(renderer, restartTexture, NULL, &restartRect);
        SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
    }
    if (ttg == tt) {
        SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);

        if (isPauseHovered) {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
            SDL_RenderFillRect(renderer, &pauseRect);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        }
    }
    if (isSoundOn)
        SDL_RenderCopy(renderer, texLoaBat, nullptr, &loaRect);
    else
        SDL_RenderCopy(renderer, texLoaTat, nullptr, &loaRect);
    SDL_RenderPresent(renderer);
}
void Game::thoatgame() {
    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
                return;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_KEYDOWN) {
                int x = e.button.x;
                int y = e.button.y;
                if (GameOver) {
                    SDL_Rect quitRect = { 200, 450, 240, 80 };

                    if (x >= quitRect.x && x <= quitRect.x + quitRect.w &&
                        y >= quitRect.y && y <= quitRect.y + quitRect.h) {
                        ttg = chosangman;
                        GameOver = false;
                        return;
                    }
                }
                if (BanThang) {
                    SDL_Rect continueRect = { 200, 350, 240, 80 };
                    if (x >= continueRect.x && x <= continueRect.x + continueRect.w &&
                        y >= continueRect.y && y <= continueRect.y + continueRect.h) {
                        if (currentlv == 1) {
                            currentlv++;
                            loadLevel(currentlv);
                            ttg = tt;
                            BanThang = false;
                            return;
                        }
                        else if (currentlv == 2) {
                            isRunning = false;
                            return;
                        }
                    }
                    SDL_Rect quitRect = { 200, 450, 240, 80 };
                    if (x >= quitRect.x && x <= quitRect.x + quitRect.w &&
                        y >= quitRect.y && y <= quitRect.y + quitRect.h) {
                        ttg = chosangman;
                        return;
                    }
                }
            }
        }
        SDL_Delay(10);
    }
}
void Game::clean() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    if (menuMusic) {
        Mix_FreeMusic(menuMusic);
        menuMusic = nullptr;
    }
    SDL_DestroyTexture(texLoaBat);
    SDL_DestroyTexture(texLoaTat);
    Mix_CloseAudio();
    if (closeButtonTexture) {
        SDL_DestroyTexture(closeButtonTexture);
        closeButtonTexture = nullptr;
    }
    if (gameMusic != nullptr) {
        Mix_FreeMusic(gameMusic);
        gameMusic = nullptr;
    }
    SDL_DestroyTexture(resumeTexture);
    SDL_DestroyTexture(restartTexture);
    SDL_DestroyTexture(exitTexture);
    IMG_Quit();
}