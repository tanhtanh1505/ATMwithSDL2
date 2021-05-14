#ifndef TA_H_
#define TA_H_

#include <SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<Windows.h>
#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<fstream>
#include<ctime>
#include<time.h>
#include<conio.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 700;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Event event;
static Mix_Chunk* soundbeep = NULL;
static bool quit = false;

static TTF_Font* fontText = NULL;

namespace TA {
	void logSDLError(std::ostream& os, const std::string& msg, bool fatal);
	void initSDL(SDL_Window*& window, SDL_Renderer*& renderer, Mix_Chunk*& soundbeep);
	void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
	SDL_Texture* loadTexture(SDL_Renderer* renderer, string path);
	void waitUntilKeyPressed();
	SDL_Texture* loadTexture(SDL_Renderer* renderer, string path);
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	bool checkCollisionWithMouse(SDL_Rect a, SDL_Event e);
	string getTimeNow();
	void renderError(SDL_Renderer* renderer, string path);
}

#endif // !1


