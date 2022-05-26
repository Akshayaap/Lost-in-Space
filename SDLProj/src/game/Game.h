#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "..\sim\Ship.h"
#include "..\sim\Maze.h"
#include "..\dsa\State.h"

#ifndef NDEBUG
#include <iostream>
#define LOG(msg) std::cout<<__FILE__<<":"<<__LINE__<<"::"<<msg<<std::endl
#else
#define LOG(msg)
#endif // !NDEBUG

class Game
{
private:
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer* renderer;
	Ship ship;
	//Maze maze;
	SDL_Texture* message;
	State state;
	TTF_Font * font;

public:
	Game(const char* title, int top, int left, int width, int height);
	~Game();
	void Go();
	void Init(const char* title,int top,int left, int width,int height);
	void Update();
	void Render();
	void Clean();
	void HandleEvents();
	inline bool IsRunning() {
		return this->isRunning;
	}
	void Reset();
	void PostProcessing();
};

