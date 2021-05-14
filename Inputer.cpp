#include "Inputer.h"

Inputer::Inputer()
{
	is_done = false;
	increaseW = rect.w;
	firstW = 0;
}

Inputer::~Inputer()
{
}

void Inputer::readNumberInput(SDL_Event event, vector<NumberButton> obn, Mix_Chunk*& soundbeep)
{
	for (int i = 0; i < obn.size() - 3; i++) {
		if (obn.at(i).clicked(event)) {
			Mix_PlayChannel(-1, soundbeep, 0);
			SDL_Delay(144);
			sread += to_string(i);
			firstW += 17;
		}
	}
	if (obn.at(12).clicked(event)) {
		Mix_PlayChannel(-1, soundbeep, 0);
		SDL_Delay(144);
		is_done = true;
	}
	else if (obn.at(11).clicked(event)) {
		Mix_PlayChannel(-1, soundbeep, 0);
		SDL_Delay(144);
		firstW = 0;
		sread = "";
	}
	else if (obn.at(10).clicked(event)) {
		Mix_PlayChannel(-1, soundbeep, 0);
	}
}

void Inputer::showInput(SDL_Renderer* renderer, int x, int y)
{
	Text showin(fontText);
	showin.setText(sread);
	showin.setRect(x, y);
	showin.setSize(firstW, showin.getRect().h);
	showin.showText(fontText, renderer);
}

int Inputer::getNumberInput()
{
	if (sread == "") {
		return 0;
	}
	else return stoi(sread);
}
