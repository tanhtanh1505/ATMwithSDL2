#include "ta.h"

void TA::logSDLError(std::ostream& os, const std::string& msg, bool fatal) {
	os << msg << " Error: " << SDL_GetError() << std::endl;
	if (fatal) {
		SDL_Quit();
		exit(1);
	}
}

void TA::initSDL(SDL_Window*& window, SDL_Renderer*& renderer, Mix_Chunk*& soundbeep) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		logSDLError(std::cout, "SDL_Init", true);
	window = SDL_CreateWindow("Hii", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    soundbeep = Mix_LoadWAV("bip.wav");
}

void TA::quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void TA::waitUntilKeyPressed()
{
	SDL_Event e;
	while (true) {
		if (SDL_WaitEvent(&e) != 0 &&
			(e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
			return;
		SDL_Delay(100);
	}
}

SDL_Texture* TA::loadTexture(SDL_Renderer* renderer, string path) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

bool TA::checkCollision(SDL_Rect a, SDL_Rect b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool TA::checkCollisionWithMouse(SDL_Rect a, SDL_Event e)
{
    int x = e.motion.x;
    int y = e.motion.y;
    if (x > a.x && x < a.x + a.w && y > a.y && y < a.y + a.h) {
        return true;
    }
    return false;
}

string TA::getTimeNow()
{
    time_t rawtime;
    time(&rawtime);
    string tc = ctime(&rawtime);
    tc.erase(tc.length() - 1, 1);
    return tc;
}

void TA::renderError(SDL_Renderer* renderer, string path)
{
    SDL_RenderClear(renderer);
    SDL_Texture* notexist = loadTexture(renderer, path);
    SDL_RenderCopy(renderer, notexist, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    notexist = NULL;
}
