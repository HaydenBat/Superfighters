#pragma once
#include "Engine.h"

class Object
{
public:
	Object(int obj_x, int obj_y, int obj_w, int obj_h, Engine* e, bool dyn);

	int getX();
	int getY();

	int getW();
	int getH();

	void setPos(float obj_x, float obj_y);

	void setRotation(float rotation);

	void update(SDL_Texture* texture, SDL_Rect* clip, Engine* e);

	void free(Engine* e);

private:
	b2Body* boxBody;

	SDL_Rect mPos;

	int mRotation;

	const float M2P = 60;
	const float P2M = 1 / M2P;
};

