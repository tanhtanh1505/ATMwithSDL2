#pragma once
#include"ta.h"
#include"Object.h"

using namespace TA;

class MenuButton : public Object
{
private:
	bool is_clicked;

public:
	MenuButton();
	~MenuButton();
	bool clicked(SDL_Event event);
};