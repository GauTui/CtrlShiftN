#include"BaseOb.h"

BaseObject::BaseObject()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	width_ = 0;
	height_ = 0;

}
BaseObject::~BaseObject()
{
	
}
bool BaseObject::loadImage(std::string file_path, SDL_Renderer* screen)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(file_path.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL)
		{
			width_ = load_surface->w;
			height_ = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object_ = new_texture;
	return p_object_ != NULL;
}