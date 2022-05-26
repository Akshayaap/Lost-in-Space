#pragma once
#include <SDL.h>
#include "Object.h"
class Ship:public Object
{
public:
	Ship();
	Ship(SDL_Renderer *renderer);
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

	inline const SDL_Rect const * GetDRect() {
		return &dRect;
	}

private:
	SDL_Texture* ship;
    SDL_Renderer*renderer;
	SDL_Rect sRect;
	SDL_Rect dRect;
};

