#pragma once
#include <SDL.h>
#include "Ship.h"


class Maze
{
private:
	SDL_Rect maze[4];
	SDL_Rect border[4];
	SDL_Rect obst;
	SDL_Rect gate;
	SDL_Renderer* renderer;

public:
	Maze();
	Maze(SDL_Renderer *renderer);
	~Maze();
	
	bool IsWinning(  Ship &ship)const ;
	bool IsHitting( Ship &ship)const;
	void Render();
};

