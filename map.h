#ifndef GAME_MAP_H
#define GAME_MAP_H

#define MAX_TILES 20

#include"commonfuc.h"
#include"BaseOb.h"


class TileMat : public BaseObject
{
public:
	TileMat() {;}
	~TileMat() {;}
};

class GameMap
{
public:
	GameMap() {;}
	~GameMap() { ; }
	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];
};


#endif