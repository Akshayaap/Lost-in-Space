#pragma once
#include "Object.h"

class Planet : public Object{
	

private:
	SDL_Texture* texture;
	SDL_Rect dRect;
public:
	Planet() = default;
	Planet(SDL_Renderer*rernderer,const Vec2& pos);
	Planet(SDL_Renderer*rernderer,const Vec2& pos, double mass);
	Planet(SDL_Renderer*rernderer,const Vec2& pos, double mass, double radius);
	~Planet();

public:
	virtual void Update()override;
	virtual void Render()override;
	virtual void Interact(const Object& obj);
	void SetTexture(const char* file);
	void SetRenderer(SDL_Renderer* renderer);
	virtual void Translate(const Vec2& dLoc);
	virtual void Scal(double s, const Vec2& v);
	
};