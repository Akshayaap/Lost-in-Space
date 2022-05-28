#pragma once
#include <SDL.h>
#include "Object.h"
class Ship:public Object
{
public:
	Ship() = default;
	Ship(SDL_Renderer *renderer);
	Ship(SDL_Renderer *renderer,const Vec2& pos);
	Ship(SDL_Renderer *renderer,const Vec2& pos,const Vec2& v);
	~Ship();

	virtual void Update()override;
	virtual void Render()override;
	virtual void PostProcessing()override;
	virtual void Reset()override;
	void Accelerate();
	void Accelerate(const Vec2 &acc);
	void Accelerate(const double acc);
	void RollLeft();
	void RollRight();
	virtual void Rotate(double t, const Vec2& pivot)override;
	virtual void Translate(const Vec2& dLoc)override;
	virtual void Scal(double s, const Vec2& center)override;
	virtual void Interact(const Object& obj)override;

	inline const SDL_Rect const * GetDRect() {
		return &dRect;
	}

private:
	SDL_Texture* ship;
    SDL_Renderer*renderer;
	SDL_Rect sRect;
	SDL_Rect dRect;
};

