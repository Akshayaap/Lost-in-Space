#include "ObjInterface.h"

ObjInterface::ObjInterface(const Object& obj,int fPoints) 
	:Object(obj)
{
	this->fPoints = fPoints;
	this->points = std::vector<Vec2>(this->fPoints);
}

void ObjInterface::Update() {

}

void ObjInterface::Render() {

}

void ObjInterface::PostProcessing() {

}

void ObjInterface::Reset() {

}
