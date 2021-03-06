#include <SDL_Image.h>
#include "Ship.h"
#include "..\math\util.h"
#include "ObjInterface.h"


 Ship::Ship(SDL_Renderer * renderer) {
	this->pos = Vec2(100, 100);
	this->radius = 35.7;

	fRect.x = 0;
	fRect.y = 0;
	fRect.w = 61;
	fRect.h = 89;

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
	 fRect.x = 0;
	 fRect.y = 0;
	 fRect.w = 61;
	 fRect.h = 89;


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

	 SDL_Surface* fireSurf = IMG_Load("fire.png");
	 fire = SDL_CreateTextureFromSurface(this->renderer, fireSurf);
	 SDL_FreeSurface(fireSurf);
 }
 
 Ship::Ship(SDL_Renderer* renderer, const Vec2& pos, const Vec2& v)
	 :Object(renderer, pos, v, 100, 35.7)
 {

	 fRect.x = 0;
	 fRect.y = 0;
	 fRect.w = 242;
	 fRect.h = 60;

	 dRect.x = this->pos.GetX() - this->radius;
	 dRect.y = this->pos.GetY() - this->radius;
	 dRect.w = 57;
	 dRect.h = 43;

#ifndef NDEBUG
	 //this->omega = .3;
#endif

	 SDL_Surface* surface = IMG_Load("ship.png");
	 ship = SDL_CreateTextureFromSurface(this->renderer, surface);
	 SDL_FreeSurface(surface);
	 
	 SDL_Surface* fireSurf = IMG_Load("fire.png");
	 fire = SDL_CreateTextureFromSurface(this->renderer, fireSurf);
	 SDL_FreeSurface(fireSurf);
 }

 Ship::~Ship() {
	 Object::~Object();
	 if (this->ship) {
		 delete this->ship;
	 }
	 if (this->fire) {
		 delete this->ship;
	 }
 }

void Ship::Update() {
	Object::Update();


#ifndef NDEBUG
	//this->pos.Rotate(omega);
#endif // !NDEBUG

	Vec2 scaled(this->pos);

	scaled -= (this->fScalCenter);
	scaled *= (this->fScal);
	scaled += (this->fScalCenter);

	scaled += this->fTrans;
	//scaled -= Vec2(this->radius * this->fScal, this->radius * this->fScal);

	this->dRect.x = scaled.GetX() - this->radius * fScal;
	this->dRect.y = scaled.GetY() - this->radius * fScal;

	this->dRect.w = 57 * fScal;
	this->dRect.h = 43 * fScal;

	Vec2 fire(this->pos-Vec2(this->radius,this->orientation));

	fire.Rotate(this->orientation, this->pos);

	fire -= (this->fScalCenter);
	fire *= (this->fScal);
	fire += (this->fScalCenter);

	fire += fTrans;

	this->fRect.x = fire.GetX() - 121 * fScal;
	this->fRect.y = fire.GetY() ;

	this->fRect.w = 121 * fScal;
	this->fRect.h = 30 * fScal;
}

void Ship::Render() {
	SDL_RenderCopyEx(this->renderer, this->ship, nullptr, &dRect,  this->orientation * 180 / PI, nullptr, SDL_FLIP_NONE);
	if (true) {
		//SDL_RenderCopyEx(this->renderer, this->fire, nullptr, &fRect, this->orientation * 180 / PI, nullptr, SDL_FLIP_NONE);
	}
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

	SDL_Surface* fireSurf = IMG_Load("fire.png");
	fire = SDL_CreateTextureFromSurface(this->renderer, fireSurf);
	SDL_FreeSurface(fireSurf);

	if (this->slave) {
		this->slave->SetRenderer(renderer);
	}
}