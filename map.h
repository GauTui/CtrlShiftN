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
	Map getMap() const { return game_map_; };
	void SetMapXY(Map& map_data) { game_map_ = map_data; }
	//char* file_name_;
private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];
};


#endif