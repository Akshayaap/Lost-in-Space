#include <SDL_Image.h>
#include "Ship.h"
#include "..\math\util.h"


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

	this->dRect.x = this->fScal * (this->pos.GetX() - fScalCenter.GetX()) + fScalCenter.GetX() + fTrans.GetX();
	this->dRect.y =  (fScal * (this->pos.GetY() - fScalCenter.GetY()) + fScalCenter.GetY() + fTrans.GetY());

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
	this->omega += 0.00001;
}

void Ship::RollLeft() {
	this->omega -= 0.00001;
}

void Ship::Reset() {
	Object::Reset();
}

void Ship::PostProcessing() {
	Object::PostProcessing();
}

void Ship::Translate(const Vec2& dLoc) {
	this->fTrans += dLoc;
	fScalCenter +=  dLoc * fScal;
}

void Ship::Scal(double s, const Vec2& center) {
	fScal *= s;
	this->fScalCenter = center;
	fScalCenter /= fScal;
}

void Ship::Rotate(double t, const Vec2& pivot) {
	
}

void Ship::Interact(const Object& obj) {
	Object::Interact(obj);
}