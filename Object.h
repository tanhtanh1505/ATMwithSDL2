#pragma once
#include"ta.h"

class Object
{
protected:
	SDL_Rect rect;
	SDL_Texture* body;
public:
	Object();
	~Object();
	void show(SDL_Renderer* renderer);
	void loadImg(SDL_Renderer* renderer, string path);
	void setSize(const int w, const int h) {
		rect.w = w;
		rect.h = h;
	}
	void setRect(const int x, const int y) {
		rect.x = x;
		rect.y = y;
	}
	SDL_Rect getRect() const { return rect; }

};

