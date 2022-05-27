#include <SDL_image.h>
#include "Planet.h"
#include "..\gfx\SDL_Extension.h"
Planet::Planet(SDL_Renderer*renderer,const Vec2& pos)
	:Object(renderer,pos)
{
}

Planet::Planet(SDL_Renderer*renderer,const Vec2& pos,double mass)
	:Object(renderer,pos,Vec2(0,0),mass)
{
	
}

Planet::Planet(SDL_Renderer*renderer,const Vec2& pos, double mass,double radius)
	:Object(renderer,pos,Vec2(0,0),mass,radius)
{
	SetTexture("earth.png");
}

void Planet::Update() {
	Object::Update();
}

void Planet::Render() {
	SDL_Rect rect =  { 522,500,200,200 };
	SDL_RenderCopy(renderer, earth, nullptr,&rect );
	//SDL_SetRenderDrawColor(this->renderer, 10, 100, 255, 255);
	//SDL_RenderFillCircle(this->renderer, this->pos.GetX(), this->pos.GetY(), this->radius);
}

void Planet::SetTexture(const char* file) {
	SDL_Surface* surface = IMG_Load(file);
 	earth = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

}