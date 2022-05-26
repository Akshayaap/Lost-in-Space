#include "Maze.h"


Maze::Maze() {

}
Maze::Maze(SDL_Renderer *renderer) {
	this->renderer = renderer;
	
	border[0].x = 0;
	border[0].y = 0;
	border[0].w = 1366;
	border[0].h = 10;

	border[1].x = 0;
	border[1].y = 0;
	border[1].w = 10;
	border[1].h = 768;

	border[2].x = 0;
	border[2].y = 768-10;
	border[2].w = 1366;
	border[2].h = 10;

	border[3].x = 1366 - 10;
	border[3].y = 0;
	border[3].w = 10;
	border[3].h = 768;


	maze[0].x = 300;
	maze[0].y = 50;
	maze[0].w = 20;
	maze[0].h = 300;

	maze[1].x = 300;
	maze[1].y = 450;
	maze[1].w = 20;
	maze[1].h = 270;

	maze[2].x = 800;
	maze[2].y = 50;
	maze[2].w = 20;
	maze[2].h = 300;

	maze[3].x = 800;
	maze[3].y = 450;
	maze[3].w = 20;
	maze[3].h = 270;


	obst.x = 550;
	obst.y = 150;
	obst.w = 20;
	obst.h = 500;

	gate.x = 1000;
	gate.y = 150;
	gate.w = 20;
	gate.h = 500;

}

Maze::~Maze() {

}


void Maze::Render() {
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 127, 255);
	for (auto& i : border) {
		SDL_RenderFillRect(this->renderer, &i);
	}

	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	for (auto& i : maze) {
		SDL_RenderFillRect(this->renderer, &i);
	}

	SDL_RenderFillRect(this->renderer, &obst);

	SDL_SetRenderDrawColor(this->renderer, 0,  255, 0, 255);
	SDL_RenderFillRect(this->renderer, &gate);
}

bool Maze::IsWinning( Ship &ship) const{
	return SDL_HasIntersection(&gate, ship.GetDRect());
}

bool Maze::IsHitting( Ship& ship) const{
	for (auto& i : border) {
		if (SDL_HasIntersection(&i, ship.GetDRect())) {
			return true;
		}
	}

	for (auto& i : maze) {
		if (SDL_HasIntersection(&i, ship.GetDRect())) {
			return true;
		}
	}

	return SDL_HasIntersection(&obst, ship.GetDRect());
}