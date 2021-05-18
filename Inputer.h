#pragma once
#include"ta.h"
#include"Object.h"
#include"NumberButton.h"
#include"Text.h"

class Inputer : public Object
{
private:
	bool is_done;
	string sread;
	int increaseW;
	int firstW;

public:
	Inputer();
	~Inputer();
	bool done() { return is_done; }
	void setDone(bool ok) { is_done = ok; }
	bool readNumberInput(SDL_Event event, vector<NumberButton> obn, Mix_Chunk*& soundbeep);
	string getInput() { return sread; }
	void showInput(SDL_Renderer* renderer, int x, int y);
	int getNumberInput();
	void clear() { sread = ""; }
};

