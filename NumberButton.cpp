#include "NumberButton.h"

NumberButton::NumberButton()
{

}

NumberButton::~NumberButton()
{
}

bool NumberButton::clicked(SDL_Event event)
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
