#include <string>
#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
SDL_Texture* g_bkground = NULL;

bool Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return false;
    }

    g_window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL) {
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == NULL) {
        return false;
    }

    return true;
}

SDL_Texture* LoadImage(const std::string& file_path) {
    SDL_Surface* load_image = IMG_Load(file_path.c_str());
    if (load_image == NULL) {
        return NULL;
    }

    SDL_Texture* optimize_image = SDL_CreateTextureFromSurface(g_renderer, load_image);
    SDL_FreeSurface(load_image);
    return optimize_image;
}

void ApplySurface(SDL_Texture* texture, int x, int y) {
    SDL_Rect destRect = { x, y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(g_renderer, texture, NULL, &destRect);
}

void CleanUp() {
    SDL_DestroyTexture(g_bkground);
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
}

int main(int argc, char* argv[]) {
    bool is_quit = false;
    SDL_Event e;

    if (!Init()) {
        return 0;
    }

    g_bkground = LoadImage("bg2.png");
    if (g_bkground == NULL) {
        return 0;
    }

    SDL_RenderClear(g_renderer);
    ApplySurface(g_bkground, 0, 0);
    SDL_RenderPresent(g_renderer);

    while (!is_quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                is_quit = true;
                break;
            }
        }
    }

    CleanUp();
    SDL_Quit();
    return 1;
}
