#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//thong so man hinh()()()
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

//thong so ve kich thuoc man hinh()()()()()-24021414

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 0xff;

#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

typedef struct input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
}input;

typedef struct Map
{
	int start_x;
	int start_y;
	int max_x;
	int max_y;
	int tile[MAX_MAP_X][MAX_MAP_Y];
}Map;
#endif


