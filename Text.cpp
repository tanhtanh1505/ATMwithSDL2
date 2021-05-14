#include "Text.h"

Text::Text(TTF_Font*& fontText)
{
	setSize(17, 28);
	setColor(WHITE);
	if (TTF_Init() == -10) {
		cout << 1;
	}
	fontText = TTF_OpenFont("font.ttf", 80);
	if (fontText == NULL) {
		cout << 1;
	}
}

Text::~Text()
{
	SDL_FreeSurface(textSurface);
}


void Text::setColor(const int& type)
{
	if (type == RED) {
		SDL_Color color = { 255, 0, 0 };
		text_color = color;
	}
	else if (type == WHITE) {
		SDL_Color color = { 136, 116, 63 };
		text_color = color;
	}
	else {
		SDL_Color color = { 0,0,0 };
		text_color = color;
	}
}

void Text::showText(TTF_Font* fontText, SDL_Renderer* renderer)
{
	textSurface = TTF_RenderText_Solid(fontText, str.c_str(), text_color);
	body = SDL_CreateTextureFromSurface(renderer, textSurface);
	show(renderer);
}

void Text::showWithoutRect(TTF_Font* fontText, SDL_Renderer* renderer)
{
	textSurface = TTF_RenderText_Solid(fontText, str.c_str(), text_color);
	body = SDL_CreateTextureFromSurface(renderer, textSurface);
}
