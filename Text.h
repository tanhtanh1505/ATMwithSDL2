#pragma once
#include"ta.h"
#include"Object.h"

using namespace TA;

class Text : public Object
{
private:
	string str;
	SDL_Color text_color;
	SDL_Surface* textSurface;

public:
	enum TextColor {
		RED = 0,
		WHITE = 1,
		BLACK = 2,
	};
	Text(TTF_Font*& fontText);
	~Text();
	void setText(string t) {
		str = t;
	}
	void setColor(const int& type);
	void showText(TTF_Font* fontText, SDL_Renderer* renderer);
	void showWithoutRect(TTF_Font* fontText, SDL_Renderer* renderer);


};

