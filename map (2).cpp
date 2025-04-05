#include"map.h"

void GameMap::LoadMap(char* name) {
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL) {
		return;
	}
	game_map_.max_x = 0;
	game_map_.max_y = 0;
	for (int i = 0; i < MAX_MAP_Y; ++i) {
		for (int j = 0; j < MAX_MAP_X; ++j) {
			fscanf_s(fp, "%d", &game_map_.tile[j][i]);
			int val = game_map_.tile[j][i];
			if (val > 0) {
				if (j > game_map_.max_x) {
					game_map_.max_x = j;
				}
				if (i > game_map_.max_y) {
					game_map_.max_y = i;
				}
			}
		}
	}
	game_map_.max_x = (game_map_.max_x + 1) * TILE_SIZE;
	game_map_.max_y = (game_map_.max_y + 1) * TILE_SIZE;

	game_map_.start_x = 0;
	game_map_.start_y = 0;

	game_map_.file_name_ = name;
	fclose(fp);

}
void GameMap::LoadTiles(SDL_Renderer* screen) {
	char file_img[20];
	FILE* fbp = NULL;
	for (int i = 0; i < MAX_TILES; i++) {
		sprintf_s(file_img, "img/%d.png", i);
		fopen_s(&fbp, file_img, "rb");
		if (fbp == NULL) {
			continue;
		}
		fclose(fbp);
	}
}
void GameMap::DrawMap(SDL_Renderer* screen) {
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	
	int map_x = 0;
	int map_y = 0;

	map_x = game_map_.start_x / TILE_SIZE;
	x1 = (game_map_.start_x % TILE_SIZE)* -1;
	x2 = x1 + SCREEN_WIDTH + (x1 ==0 ? 0 : TILE_SIZE);

	map_y = game_map_.start_y / TILE_SIZE;
	y1 = (game_map_.start_y % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE) {
		map_x = game_map_.start_x / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) {
			int val = game_map_.tile[map_x][map_y];
			if (val > 0) {
				tile_mat_[val].setRect(j, i);
				tile_mat_[val].render(screen);
			}
			map_x++;

		}
		map_y++;
	}

}