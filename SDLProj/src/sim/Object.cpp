#include "Object.h"
#include "ObjInterface.h"
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
{
//	this->slave = new ObjInterface(this);
}

Object::Object(const Object& obj) {
	this->acc = obj.acc;
	this->v = obj.v;
	this->pos = obj.pos;
	this->force = obj.force;
	this->fScal = obj.fScal;
	this->fTrans = obj.fTrans;
	this->fScalCenter = obj.fScalCenter;
	this->mass = obj.mass;
	this->omega = obj.omega;
	this->orientation = obj.orientation;

	this->slave = new ObjInterface(this);
}

Object::Object(SDL_Renderer* renderer)
	:
	pos(0, 0), v(0, 0), acc(0, 0), omega(0), mass(100), radius(10), orientation(0), force(0, 0)
{
	this->renderer = renderer;
	this->slave = new ObjInterface(this);

}

Object::~Object(){
	if (this->slave) {
		delete this->slave;
	}
}

Object::Object( SDL_Renderer*renderer,const Vec2& pos,const   Vec2& v) 
	:
	pos(pos), v(v), acc(0, 0), omega(0), mass(100), radius(10), orientation(0), force(0, 0)
{
	this->renderer = renderer;
	this->slave = new ObjInterface(this);

}

Object::Object(SDL_Renderer*renderer,const  Vec2& pos, const  Vec2& v, double mass)
	:
	pos(pos), v(v), acc(0, 0), omega(0), mass(mass), radius(10), orientation(0), force(0, 0)
{
	this->renderer=renderer;
	this->slave = new ObjInterface(this);

}

Object::Object(SDL_Renderer*renderer,const  Vec2& pos,const   Vec2& v, double mass, double radius)
	:
	pos(pos), v(v), acc(0, 0), omega(0), mass(mass), radius(radius), orientation(0), force(0, 0)
{
	this->renderer=renderer;
	this->slave = new ObjInterface(this);
}

void Object :: Update() {
	this->acc = this->force / this->mass;
	this->v += this->acc;
	this->pos += this->v;
	this->orientation=wrapAngle( this->orientation += this->omega );
	this->force.SetXY(0, 0);
}

void Object::Render() {}

void Object::Rotate(double t,const Vec2& pivot) {}

void Object::Translate(const Vec2& v) {
	this->fTrans += v;
}

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

	if ((this->radius + obj.radius) * (this->radius + obj.radius) <= sDist) {
		//Collision Handling code
	}

	double force = 0.1 * this->mass * obj.mass / sDist;
	Vec2 dir = (  this->pos - obj.pos).Norm();
	dir *= force;
	this->force -= dir;
}
void Object::SetRenderer(SDL_Renderer* renderer) {
	
}