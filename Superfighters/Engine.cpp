#include "Engine.h"

bool init(std::string name, int width, int height, Engine* e)
{
	SDL_Init(SDL_INIT_VIDEO | IMG_INIT_PNG | IMG_INIT_JPG);

	e->window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	e->renderer = SDL_CreateRenderer(e->window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(e->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	SDL_RenderClear(e->renderer);

	b2Vec2 gravity(0.0f, 9.81f);
	e->world = new b2World(gravity);

	return true;
}

void render(Engine* e)
{
	SDL_RenderPresent(e->renderer);
}

void clear(Engine* e)
{
	SDL_RenderClear(e->renderer);
}

void stop(Engine* e)
{
	SDL_DestroyWindow(e->window);
	e->window = NULL;
	SDL_DestroyRenderer(e->renderer);
	e->renderer = NULL;
	SDL_Quit();
	IMG_Quit();
}