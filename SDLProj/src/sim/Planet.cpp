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

Planet::~Planet() {
	Object::~Object();
	if (this->texture) {
		delete this->texture;
	}
}

void Planet::Update() {
	Object::Update();
	Vec2 sCenter();

	Vec2 scaled(this->pos.GetX() + fTrans.GetX() - this->radius, this->pos.GetY() + fTrans.GetY() - this->radius);
	scaled -= (this->fScalCenter);
	scaled *= (this->fScal);
	scaled += (this->fScalCenter);

	this->dRect.x = scaled.GetX();
	this->dRect.y = scaled.GetY();
	
	this->dRect.w = 2 * this->radius * fScal;
	this->dRect.h = 2 * this->radius * fScal;
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

void Planet::Translate(const Vec2& dLoc){
Object::Translate(dLoc);
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

void Planet::Scal(double s, const Vec2& v) {
	Object::Scal(s, v);
}