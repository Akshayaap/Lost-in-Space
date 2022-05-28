#pragma once
#include <vector>
#include "..\math\Vec2.h"
#include "Object.h"

class ObjInterface:public Object{
public:
	ObjInterface() = delete;
	ObjInterface(const Object& obj, int fPoints = 200);
	ObjInterface(const ObjInterface& objInt) = delete;
	ObjInterface& operator = (const ObjInterface& objInt) = delete;

public:
	//virtual void Trajectory(std::vector<Vec2>,int fPoint = 200);
	virtual void Render()override;
	virtual void Update()override;
	virtual void Reset() override;
	virtual void Interact(const Object& obj)override;
	virtual void PostProcessing()override;

public:
	

protected:
	int fPoints = 200;
	std::vector<Vec2> points;
};

