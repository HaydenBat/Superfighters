#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <box2d/box2d.h>
#include <string>

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	b2World* world;
}Engine;

bool init(std::string name, int width, int height, Engine* e);

void render(Engine* e);

void clear(Engine* e);

void stop(Engine* e);