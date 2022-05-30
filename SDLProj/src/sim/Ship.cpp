#include <SDL_Image.h>
#include "Ship.h"
#include "..\math\util.h"
#include "ObjInterface.h"


 Ship::Ship(SDL_Renderer * renderer) {
	this->pos = Vec2(100, 100);
	this->radius = 35.7;

	sRect.x = 0;
	sRect.y = 0;
	sRect.w = 57;
	sRect.h = 43;

	 dRect.x = this->pos.GetX() - this->radius;
	 dRect.y = -this->pos.GetY() - this->radius;
	 dRect.w = 57;
	 dRect.h = 43;

	 this->renderer = renderer;

	 SDL_Surface* surface = IMG_Load("ship.png");
	 ship = SDL_CreateTextureFromSurface(this->renderer, surface);
	 SDL_FreeSurface(surface);
}

 Ship::Ship(SDL_Renderer* renderer, const Vec2& pos) {
	 sRect.x = 0;
	 sRect.y = 0;
	 sRect.w = 57;
	 sRect.h = 43;


	 this->pos = pos;
	 this->radius = 35.7;

	 dRect.x = this->pos.GetX() - this->radius;
	 dRect.y = this->pos.GetY() - this->radius;
	 dRect.w = 57;
	 dRect.h = 43;

	 this->renderer = renderer;

	 SDL_Surface* surface = IMG_Load("ship.png");
	 ship = SDL_CreateTextureFromSurface(this->renderer, surface);
	 SDL_FreeSurface(surface);
 }
 
 Ship::Ship(SDL_Renderer* renderer, const Vec2& pos, const Vec2& v)
	 :Object(renderer, pos, v, 100, 35.7)
 {

	 sRect.x = 0;
	 sRect.y = 0;
	 sRect.w = 57;
	 sRect.h = 43;

	 dRect.x = this->pos.GetX() - this->radius;
	 dRect.y = this->pos.GetY() - this->radius;
	 dRect.w = 57;
	 dRect.h = 43;

	 SDL_Surface* surface = IMG_Load("ship.png");
	 ship = SDL_CreateTextureFromSurface(this->renderer, surface);
	 SDL_FreeSurface(surface);
 }

 Ship::~Ship() {
	 Object::~Object();
	 if (this->ship) {
		 delete this->ship;
	 }
 }

void Ship::Update() {
	Object::Update();


#ifndef NDEBUG
	//this->pos.Rotate(omega);
#endif // !NDEBUG

	Vec2 scaled(this->pos.GetX() + fTrans.GetX() - this->radius, this->pos.GetY() + fTrans.GetY() - this->radius);
	scaled -= (this->fScalCenter);
	scaled *= (this->fScal);
	scaled += (this->fScalCenter);

	this->dRect.x = scaled.GetX();
	this->dRect.y = scaled.GetY();

	this->dRect.w = 57 * fScal;
	this->dRect.h = 43 * fScal;
}

void Ship::Render() {
	SDL_RenderCopyEx(this->renderer, this->ship, &sRect, &dRect,  this->orientation * 180 / PI, nullptr, SDL_FLIP_NONE);
}

void Ship::Accelerate() {
	this->v += this->acc;
	this->slave->SetVel(this->v);
}

void Ship::Accelerate(const Vec2& acc) {
	this->v += acc;
	this->slave->SetVel(this->v);
}

void Ship::Accelerate(const double acc) {
	this->v += Vec2(acc,this->orientation,true);
	this->slave->SetVel(this->v);
}

void Ship::RollRight() {
	this->omega += 0.01;
	this->slave->SetOmega(this->omega);
}

void Ship::RollLeft() {
	this->omega -= 0.01;
	this->slave->SetOmega(this->omega);
}

void Ship::Reset() {
	Object::Reset();
}

void Ship::PostProcessing() {
	Object::PostProcessing();
}

void Ship::Translate(const Vec2& dLoc) {
	Object::Translate(dLoc);
}

void Ship::Scal(double s, const Vec2& center) {
	Object::Scal(s, center);
}

void Ship::Rotate(double t, const Vec2& pivot) {
	
}

void Ship::Interact(const Object& obj) {
	Object::Interact(obj);
}

void Ship::SetRenderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
	SDL_Surface* surface = IMG_Load("ship.png");
	ship = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

	if (this->slave) {
		this->slave->SetRenderer(renderer);
	}
}