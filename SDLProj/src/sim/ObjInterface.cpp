#include "ObjInterface.h"

ObjInterface::ObjInterface(const Object* obj,int fPoints) 
{
	this->acc = obj->GetAcc();
	this->v = obj->GetVel();
	this->pos = obj->GetPos();
	this->force = obj->GetForce();
	this->fScal = obj->GetFScal();
	this->fTrans = obj->GetFTran();

	this->slave = nullptr;
	this->malik = (Object*)obj;
}

ObjInterface::~ObjInterface() {

}

void ObjInterface::Update() {
	Object::Update();
	this->current++;
	if (this->current >= PATH_LENGTH) {
		this->current = 0;
	}	

	Vec2 scaled(this->pos);

	scaled -= (this->fScalCenter);
	scaled *= (this->fScal);
	scaled += (this->fScalCenter);

	scaled += this->fTrans;
	
	this->points[current] = scaled;
}

void ObjInterface::Render() {
	//Object::Render();
	int first = (current + 1) % PATH_LENGTH;
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	if (first > current) {
		for (int i = first; i < PATH_LENGTH-1; i++) {
			SDL_RenderDrawLine(this->renderer, this->points[i].GetX() -this->radius, this->points[i].GetY() - this->radius, this->points[i + 1].GetX() - this->radius , this->points[i + 1].GetY() - this->radius);
		}
		SDL_RenderDrawLine(this->renderer, this->points[PATH_LENGTH - 1].GetX() - this->radius, this->points[PATH_LENGTH - 1].GetY()  - this->radius, this->points[0].GetX()  - this->radius, this->points[0].GetY() - this->radius);
		for (int i = 0; i < current; i++) {
			SDL_RenderDrawLine(this->renderer, this->points[i].GetX()  - this->radius, this->points[i].GetY()  - this->radius, this->points[i + 1].GetX()  - this->radius, this->points[i + 1].GetY()  - this->radius);
		}
	}
	else {
		for (int i = first; i < current; i++) {
			SDL_RenderDrawLine(this->renderer, this->points[i].GetX()  - this->radius, this->points[i].GetY()  - this->radius, this->points[i + 1].GetX()  - this->radius, this->points[i + 1].GetY() - this->radius);
		}
	}
}

void ObjInterface::PostProcessing() {
	Object::PostProcessing();
}

void ObjInterface::Reset() {
	this->acc = malik->GetAcc();
	this->v = malik->GetVel();
	this->pos = malik->GetPos();
	this->force = malik->GetForce();
	this->fScal = malik->GetFScal();
	this->fTrans = malik->GetFTran();
	this->fScalCenter = malik->GetFScalCenter();
	this->mass = malik->GetMass();
	this->omega = malik->GetOmega();
	this->orientation = malik->GetOrientation();
}

void ObjInterface::Interact(const Object &obj) {
	Object::Interact(obj);
}

void ObjInterface::Clear() {
	this->current = -1;
}

void ObjInterface::SetRenderer(SDL_Renderer*renderer) {
	this->renderer = renderer;
}

void ObjInterface::Translate(const Vec2& dLoc) {
	Object::Translate(dLoc);
}