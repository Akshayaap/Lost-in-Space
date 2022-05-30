#include <SDL_image.h>
#include "Planet.h"
#include "..\gfx\SDL_Extension.h"
#include "ObjInterface.h"

Planet::Planet(SDL_Renderer*renderer,const Vec2& pos)
	:Object(renderer,pos)
{
	SetTexture("moon.png");
}

Planet::Planet(SDL_Renderer*renderer,const Vec2& pos,double mass)
	:Object(renderer,pos,Vec2(0,0),mass)
{
	SetTexture("moon.png");
}

Planet::Planet(SDL_Renderer*renderer,const Vec2& pos, double mass,double radius)
	:Object(renderer,pos,Vec2(0,0),mass,radius)
{
	SetTexture("moon.png");
	this->dRect.w = radius * 2;
	this->dRect.h = radius * 2;
}

void Planet::Update() {
	Object::Update();
	this->dRect.x = this->pos.GetX() + fTrans.GetX() - this->radius;
	this->dRect.y = this->pos.GetY() + fTrans.GetY() - this->radius;
	
}

void Planet::Render() {

	SDL_RenderCopy(renderer, texture, nullptr,&dRect );
	//SDL_SetRenderDrawColor(this->renderer, 10, 100, 255, 255);
	//SDL_RenderFillCircle(this->renderer, this->pos.GetX(), this->pos.GetY(), this->radius);
}

void Planet::SetTexture(const char* file) {
	SDL_Surface* surface = IMG_Load(file);
 	texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

}

void Planet::Translate(const Vec2& dLoc) {
	this->fTrans += dLoc;
	if (this->slave) {
		this->slave->Translate(dLoc);
	}
}

void Planet::Interact(const Object& obj) {
	Object::Interact(obj);

	//NFT
}
void Planet::SetRenderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
	SDL_Surface* surface = IMG_Load("moon.png");
	texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
	if (this->slave) {
		this->slave->SetRenderer(renderer);
	}

}