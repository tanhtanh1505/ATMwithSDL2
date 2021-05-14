#pragma once
#include"ta.h"
#include"Object.h"

using namespace TA;

class NumberButton: public Object
{
private:
	bool is_clicked;

public:
	NumberButton();
	~NumberButton();
	bool clicked(SDL_Event event);
};

