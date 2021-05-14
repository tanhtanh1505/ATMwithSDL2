#include "Object.h"

Object::Object()
{
	rect.x = 10;
	rect.y = 10;
	rect.w = 32;
	rect.h = 13;
	body = NULL;
}

Object::~Object()
{
	SDL_DestroyTexture(body);
}

void Object::show(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, body, NULL, &rect);
}

void Object::loadImg(SDL_Renderer* renderer, string path)
{
	body = TA::loadTexture(renderer, path);
}
