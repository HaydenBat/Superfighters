#include "Player.h"

Player::Player(int obj_x, int obj_y, int obj_w, int obj_h, Engine* e)
{
	moveState = MS_STOP;

	obj_x += (obj_w / 2);
	obj_y += (obj_h / 2);

	mRotation = 0.0f;

	mPos.x = obj_x;
	mPos.y = obj_y;
	mPos.w = obj_w;
	mPos.h = obj_h;

	//Physics

	b2BodyDef playerBodyDef;
	playerBodyDef.position.Set(obj_x * P2M, obj_y * P2M);
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.fixedRotation = true;
	playerBody = e->world->CreateBody(&playerBodyDef);

	b2PolygonShape playerShape;
	playerShape.SetAsBox(P2M * obj_w / 2 - playerShape.m_radius, P2M * obj_h / 2 - playerShape.m_radius);

	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &playerShape;
	playerFixtureDef.density = 1.0f;
	playerBody->CreateFixture(&playerFixtureDef);

}

int Player::getX() { return mPos.x; }
int Player::getY() { return mPos.y; }

int Player::getW() { return mPos.w; }
int Player::getH() { return mPos.h; }

void Player::setPos(float obj_x, float obj_y)
{
	mPos.x = obj_x;
	mPos.y = obj_y;

}

void Player::setRotation(float rotation)
{
	mRotation = rotation;
}

void Player::update(SDL_Texture* texture, SDL_Rect* clip, Engine* e)
{
	b2Vec2 vel = playerBody->GetLinearVelocity();
	switch (moveState)
	{
	case MS_LEFT:  vel.x = -5; break;
	case MS_STOP:  vel.x = 0; break;
	case MS_RIGHT: vel.x = 5; break;
	}
	playerBody->SetLinearVelocity(vel);

	mRotation = playerBody->GetAngle() * 180 / M_PI;
	mPos.x = playerBody->GetPosition().x * M2P - (mPos.w / 2);
	mPos.y = playerBody->GetPosition().y * M2P - (mPos.h / 2);
	

	SDL_RenderCopyEx(e->renderer, texture, clip, &mPos, mRotation, NULL, SDL_FLIP_NONE);
}

void Player::free(Engine* e)
{
	e->world->DestroyBody(playerBody);
	playerBody = NULL;
}

void Player::handleEvent(SDL_Event& e)
{
	float impulse = playerBody->GetMass() * -10;
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: playerBody->ApplyLinearImpulse(b2Vec2(0, impulse), playerBody->GetWorldCenter(), false); break;
		case SDLK_LEFT: moveState = MS_LEFT; break;
		case SDLK_RIGHT: moveState = MS_RIGHT; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: moveState = MS_STOP; break;
		case SDLK_RIGHT: moveState = MS_STOP; break;
		}
	}
}