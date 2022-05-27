#pragma once
#include "Object.h"

class Planet : public Object{
	

private:
	SDL_Texture* earth;
public:
	Planet() = default;
	Planet(SDL_Renderer*rernderer,const Vec2& pos);
	Planet(SDL_Renderer*rernderer,const Vec2& pos, double mass);
	Planet(SDL_Renderer*rernderer,const Vec2& pos, double mass, double radius);

public:
	void Update()override;
	void Render()override;
	void SetTexture(const char* file);
	
};