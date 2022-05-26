#include "Object.h"
#include "..\math\util.h"



Object::Object(Vec2& pos)
	:
	v(0,0),acc(0,0),omega(0)
{
	this->pos = pos;
}


Object::Object() :v(0, 0), acc(0, 0) ,pos(0,0),omega(0){}

Object::~Object(){}


void Object :: Update() {
	this->pos += this->v;
	this->orientation=wrapAngle( this->orientation += this->omega );
}

void Object::Render() {}

void Object::Rotate(double t) {}

void Object::Translate(const Vec2& v) {}

void Object::Scal(double s) {}

void Object::PostProcessing() {}

void Object::Reset() {
	this->acc.SetXY(0, 0);
	this->v.SetXY(0, 0);
	this->pos.SetXY(0, 0);
	this->orientation = 0;
	this->omega = 0;
}