#include "MenuButton.h"

MenuButton::MenuButton()
{
	setSize(44, 26);
}

MenuButton::~MenuButton()
{
}

bool MenuButton::clicked(SDL_Event event)
{
	if (checkCollisionWithMouse(rect, event)) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			return true;
		}
		else if (event.type == SDL_MOUSEBUTTONUP) {
			return false;
		}
	}
	return false;
}
