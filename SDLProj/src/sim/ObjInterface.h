#pragma once
#include <array>
#include "..\math\Vec2.h"
#include "Object.h"

#define PATH_LENGTH 200

class ObjInterface:public Object{
public:
	ObjInterface() = delete;
	ObjInterface(const Object* obj, int fPoints = 200);
	ObjInterface(const ObjInterface& objInt) = delete;
	ObjInterface& operator = (const ObjInterface& objInt) = delete;

public:
	//virtual void Trajectory(std::vector<Vec2>,int fPoint = 200);
	virtual void Render() override;
	virtual void Update()override;
	virtual void Reset() override;
	virtual void Interact(const Object& obj)override;
	virtual void PostProcessing()override;
	void Clear();
	inline Object* GetMalik() {
		return this->malik;
	}
	void SetRenderer(SDL_Renderer* renderer);

public:
	

protected:
	Object* malik = nullptr;
	std::array<Vec2,PATH_LENGTH> points;
	int current = -1;
};

