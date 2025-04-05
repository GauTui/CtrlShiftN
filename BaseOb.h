#ifndef BASEOB_H_
#define BASEOB_H_

#include"commonfuc.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void setRect(int x, int y) { rect_.x = x; rect_.y = y; }
	SDL_Rect getRect() const { return rect_; }
	SDL_Texture* getObject() const { return p_object_; }

	bool loadImage(std::string file_path,SDL_Renderer* screen);		
	void render(SDL_Renderer* des, SDL_Rect* clip = NULL);
	
	void Free();
protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
	int width_;
	int height_;
};

#endif
