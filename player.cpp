#include"Player.h"
#include"commonfuc.h"

PlayerObject::PlayerObject()
{
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	on_ground_ = false;

}
PlayerObject::~PlayerObject()
{
	
}
bool PlayerObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::loadImage(path, screen);
	if (ret == true) {
		width_frame_ = rect_.w/8;
		height_frame_ = rect_.h;
	}
	return ret;
}
void PlayerObject::set_clips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < 8; i++) {
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}
void PlayerObject::show(SDL_Renderer* des) {
	if (status_ == WALK_LEFT) {
		loadImage("img//sangtrai.png", des);
	}
	else {
		loadImage("img//sangphai.png", des);
	}
	if (input_type_.left_ == 1 || input_type_.right_ == 1) {
		frame_++;
	}
	else {
		frame_ = 0;
	}

	if (frame_ >= 8) {
		frame_ = 0;
	}

	rect_.x = x_pos_;
	rect_.y = y_pos_;

	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };
	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}
void PlayerObject::HandleInputAction(SDL_Event events,SDL_Renderer* screen) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym) {
		case SDLK_RIGHT:
			input_type_.right_ = 1;
			status_ = WALK_RIGHT;
			input_type_.left_ = 0;
			break;
		case SDLK_LEFT:
			input_type_.left_ = 1;
			status_ = WALK_LEFT;
			input_type_.right_ = 0;
			break;
		case SDLK_UP:
			input_type_.jump_ = 1;
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym) {
		case SDLK_RIGHT:
			input_type_.right_ = 0;
			break;
		case SDLK_LEFT:
			input_type_.left_ = 0;
			break;
		case SDLK_UP:
			input_type_.jump_ = 0;
			break;
		default:
			break;
		}
	}
}
void PlayerObject::DoPlay(Map& map_data) {
	x_val_ = 0;
	y_val_ += 0.8;
	if (y_val_ >= MAX_FALL_SPEED) {
		y_val_ = MAX_FALL_SPEED;
	}
	if (input_type_.left_ == 1) {
		x_val_ -= PLAYER_SPEED;
	}
	if (input_type_.right_ == 1) {
		x_val_ += PLAYER_SPEED;
	}
	CheckToMap(map_data);
}

void PlayerObject::CheckToMap(Map& map_data) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;


	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_) / TILE_SIZE;
	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val_ > 0) {
			if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0) {
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE) {
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;
	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + height_frame_ + y_val_) / TILE_SIZE;

	if (y1 >= 0 && y2 < MAX_MAP_Y && x1 >= 0 && x2 < MAX_MAP_X) {
		if (y_val_ > 0) {
			if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= height_frame_ + 1;
				y_val_ = 0;
				on_ground_ = true;
			}
		}
		else if (y_val_ < 0) {
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		}
	}
	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ >= map_data.max_x) {
		x_pos_ = map_data.max_x - width_frame_ - 1;
	}

}