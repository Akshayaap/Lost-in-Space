#include <SDL_Image.h>
#include "Ship.h"
#include "..\math\util.h"


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
 
 Ship::Ship(SDL_Renderer* renderer, const Vec2& pos, const Vec2& v) {
	 sRect.x = 0;
	 sRect.y = 0;
	 sRect.w = 57;
	 sRect.h = 43;

	 this->pos = pos;
	 this->v = v;
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

 Ship::~Ship() {}

void Ship::Update() {
	Object::Update();


#ifndef NDEBUG
	//this->pos.Rotate(omega);
#endif // !NDEBUG

	

	this->dRect.x = this->pos.GetX() + fTrans.GetX() - this->radius;
	this->dRect.y = this->pos.GetY() + fTrans.GetY() - this->radius;

	dRect.w = 57 * fScal;
	dRect.h = 43 * fScal;

}

void Ship::Render() {
	SDL_RenderCopyEx(this->renderer, this->ship, &sRect, &dRect,  this->orientation * 180 / PI, nullptr, SDL_FLIP_NONE);
}

void Ship::Accelerate() {
	this->v += this->acc;
}

void Ship::Accelerate(const Vec2& acc) {
	this->v += acc;
}

void Ship::Accelerate(const double acc) {
	this->v += Vec2(acc,this->orientation,true);
}

void Ship::RollRight() {
	this->omega += 0.01;
}

void Ship::RollLeft() {
	this->omega -= 0.01;
}

void Ship::Reset() {
	Object::Reset();
}

void Ship::PostProcessing() {
	Object::PostProcessing();
}

void Ship::Translate(const Vec2& dLoc) {
	this->fTrans += dLoc;
}

void Ship::Scal(double s, const Vec2& center) {
}

void Ship::Rotate(double t, const Vec2& pivot) {
	
}

void Ship::Interact(const Object& obj) {
	Object::Interact(obj);
}