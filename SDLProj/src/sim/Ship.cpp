#include <SDL_Image.h>
#include "Ship.h"
#include "..\math\util.h"


Ship::Ship() {}

 Ship::Ship(SDL_Renderer * renderer) {
	 sRect.x = 0;
	 sRect.y = 0;
	 sRect.w = 57;
	 sRect.h = 43;

	 dRect.x = 200;
	 dRect.y = 200;
	 dRect.w = 57;
	 dRect.h = 43;

	 this->pos = Vec2(100,100);

	 this->renderer = renderer;

	 SDL_Surface* surface = IMG_Load("ship.png");
	 ship = SDL_CreateTextureFromSurface(this->renderer, surface);
	 SDL_FreeSurface(surface);
}

 Ship::~Ship() {}

void Ship::Update() {
	Object::Update();

	this->dRect.x = this->pos.GetX() - 29;
	this->dRect.y = 600 - this->pos.GetY();
}

void Ship::Render() {
	SDL_RenderCopyEx(this->renderer, this->ship, &sRect, &dRect, - this->orientation * 180 / PI, nullptr, SDL_FLIP_NONE);
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
	this->omega -= 0.0001;
}

void Ship::RollLeft() {
	this->omega += 0.0001;
}

void Ship::Reset() {
	Object::Reset();
}

void Ship::PostProcessing() {
	Object::PostProcessing();
}