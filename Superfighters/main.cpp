#include "Engine.h"
#include "Object.h"
#include "Player.h"
#include <vector>

std::vector<Object> objects;

const int WIDTH = 1280;
const int HEIGHT = 960;

Engine e;


int main(int argc, char* args[])
{
	init("Superfighters", WIDTH, HEIGHT, &e);

	Object ground(0, HEIGHT, WIDTH, 200, &e, false);
	Player player(10, 10, 200, 200, &e);

	//Create Textures
	SDL_Surface* tmp;
	tmp = IMG_Load("res/gfx/130.png");
	SDL_Texture* box = SDL_CreateTextureFromSurface(e.renderer, tmp);
	tmp = NULL;

	tmp = IMG_Load("res/gfx/1911.png");
	SDL_Texture* jeff = SDL_CreateTextureFromSurface(e.renderer, tmp);

	//PlayerClips
	SDL_Rect playerClips[4];
	playerClips[0].x = 19;
	playerClips[0].y = 6;
	playerClips[0].w = 24;
	playerClips[0].h = 31;

	playerClips[1].x = 43;
	playerClips[1].y = 6;
	playerClips[1].w = 24;
	playerClips[1].h = 31;

	playerClips[2].x = 19;
	playerClips[2].y = 6;
	playerClips[2].w = 24;
	playerClips[2].h = 31;

	playerClips[3].x = 67;
	playerClips[3].y = 6;
	playerClips[3].w = 24;
	playerClips[3].h = 31;

	render(&e);

	int playerFrame = 0;
	bool quit = false;
	Uint32 start;
	SDL_Event event;
	while (!quit)
	{
		start = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				int w = 50, h = 50;
				int x, y;
				SDL_GetMouseState(&x, &y);

				Object obj(x - (w / 2), y - (h / 2), w, h, &e, true);
				objects.push_back(obj);
			}
			player.handleEvent(event);

		}



		ground.update(box, NULL, &e);

		SDL_Rect* currentPlayerClip = &playerClips[playerFrame / 8];
		player.update(jeff, currentPlayerClip, &e);
		++playerFrame;
		if (playerFrame / 8 >= 4)
		{
			playerFrame = 0;
		}

		e.world->Step(1.0f / 60.0f, 6, 3);
		for (Object o : objects)
		{
			o.update(box, NULL, &e);
		}

		render(&e);
		clear(&e);

		if (1000.0 / 60 > SDL_GetTicks() - start)
		{
			SDL_Delay(1000.0 / 60 - (SDL_GetTicks() - start));
		}
	}

	player.free(&e);

	ground.free(&e);

	for (Object o : objects)
	{
		o.free(&e);
	}

	stop(&e);
	return 0;
}