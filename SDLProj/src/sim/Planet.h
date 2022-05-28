#pragma once
#include "Object.h"

class Planet : public Object{
	

private:
	SDL_Texture* earth;
	SDL_Rect dRect;
public:
	Planet() = default;
	Planet(SDL_Renderer*rernderer,const Vec2& pos);
	Planet(SDL_Renderer*rernderer,const Vec2& pos, double mass);
	Planet(SDL_Renderer*rernderer,const Vec2& pos, double mass, double radius);

public:
	virtual void Update()override;
	virtual void Render()override;
	virtual void Interact(const Object& obj);
	void SetTexture(const char* file);

	virtual void Translate(const Vec2& dLoc);
	
};