#include "Object.h"

Object::Object(int obj_x, int obj_y, int obj_w, int obj_h, Engine* e, bool dyn)
{
	obj_x += (obj_w / 2);
	obj_y += (obj_h / 2);

	mRotation = 0.0f;

	mPos.x = obj_x;
	mPos.y = obj_y;
	mPos.w = obj_w;
	mPos.h = obj_h;

	//Physics

	b2BodyDef boxBodyDef;
	boxBodyDef.position.Set(obj_x * P2M, obj_y * P2M);
	if (dyn == true) { boxBodyDef.type = b2_dynamicBody; }
	else { boxBodyDef.type = b2_staticBody; }
	boxBody = e->world->CreateBody(&boxBodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(P2M * obj_w / 2 - boxShape.m_radius, P2M * obj_h / 2 - boxShape.m_radius);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1.0f;
	boxBody->CreateFixture(&boxFixtureDef);


}

int Object::getX() { return mPos.x; }
int Object::getY() { return mPos.y; }

int Object::getW() { return mPos.w; }
int Object::getH() { return mPos.h; }

void Object::setPos(float obj_x, float obj_y)
{
	mPos.x = obj_x;
	mPos.y = obj_y;

}

void Object::setRotation(float rotation)
{
	mRotation = rotation;
}

void Object::update(SDL_Texture* texture, SDL_Rect* clip, Engine* e)
{
	mRotation = boxBody->GetAngle() * 180 / M_PI;
	mPos.x = boxBody->GetPosition().x * M2P - (mPos.w / 2);
	mPos.y = boxBody->GetPosition().y * M2P - (mPos.h / 2);

	SDL_Rect renderQuad = {mPos.x, mPos.y, mPos.w, mPos.h};
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(e->renderer, texture, clip, &renderQuad, mRotation, NULL, SDL_FLIP_NONE);
}

void Object::free(Engine* e)
{
	e->world->DestroyBody(boxBody);
	boxBody = NULL;
}