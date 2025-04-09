#ifndef MAIN_OBJECTS_PLAYER_H_
#define MAIN_OBJECTS_PLAYER_H_


#include"BaseOb.h"
#include"commonfuc.h"

#define MAX_FALL_SPEED 10
#define GRAVITY_SPEED 1
#define PLAYER_SPEED 7

#define BLANK_TILE 0
#define PLAYER_JUMP_VAL 15

class PlayerObject : public BaseObject {
public:
	PlayerObject();
	~PlayerObject();
	enum WalkType
	{
		WALK_LEFT = 1,
		WALK_RIGHT = 0,
	};
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void DoPlay(Map& map_data);
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }
	void CenterEntityOnMap(Map& map_data);
private:
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];
	int frame_;
	int status_;
	input input_type_;
	bool on_ground_;
	int map_x_;
	int map_y_;

};

#endif

