#include "Object.h"
#include "..\math\util.h"


Object::Object(SDL_Renderer*renderer,const Vec2& pos)
	:
	pos(pos), v(0, 0) ,acc(0, 0) ,omega(0) ,mass(100), radius(10),orientation(0),force(0,0)
{
	this->renderer = renderer;
}


Object::Object() 
	:
	pos(0, 0), v(0, 0) ,acc(0, 0) ,omega(0) ,mass(100), radius(10), orientation(0), force(0, 0)
{}

Object::Object(SDL_Renderer* renderer)
	:
	pos(0, 0), v(0, 0), acc(0, 0), omega(0), mass(100), radius(10), orientation(0), force(0, 0)
{
	this->renderer = renderer;
}

Object::~Object(){}

Object::Object( SDL_Renderer*renderer,const Vec2& pos,const   Vec2& v) 
	:
	pos(pos), v(v), acc(0, 0), omega(0), mass(100), radius(10), orientation(0), force(0, 0)
{
	this->renderer = renderer;
}

Object::Object(SDL_Renderer*renderer,const  Vec2& pos, const  Vec2& v, double mass)
	:
	pos(pos), v(v), acc(0, 0), omega(0), mass(mass), radius(10), orientation(0), force(0, 0)
{
	this->renderer=renderer;
}

Object::Object(SDL_Renderer*renderer,const  Vec2& pos,const   Vec2& v, double mass, double radius)
	:
	pos(pos), v(v), acc(0, 0), omega(0), mass(mass), radius(radius), orientation(0), force(0, 0)
{
	this->renderer=renderer;
}

void Object :: Update() {
	this->acc = this->force * (1 / this->mass);
	this->pos += this->v;
	this->orientation=wrapAngle( this->orientation += this->omega );
}

void Object::Render() {}

void Object::Rotate(double t,const Vec2& pivot) {}

void Object::Translate(const Vec2& v) {}

void Object::Scal(double s,const Vec2& ) {}

void Object::PostProcessing() {}

void Object::Reset() {
	this->acc.SetXY(0, 0);
	this->v.SetXY(0, 0);
	this->pos.SetXY(0, 0);
	this->orientation = 0;
	this->omega = 0;
}

void Object::Interact(const Object& obj) {
	double sDist = (this->pos.GetX() - obj.pos.GetX()) * (this->pos.GetX() - obj.pos.GetX()) + (this->pos.GetY() - obj.pos.GetY()) * (this->pos.GetY() - obj.pos.GetY());
	double force = this->mass * obj.mass / sDist;
	Vec2 dir = (this->pos - obj.pos).Norm();
	dir *= force;
	this->force += force;
}