#pragma once
#include <SDL.h>
class Game
{
private:
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer* renderer;


public:
	Game(const char* title, int top, int left, int width, int height);
	~Game();
	void Init(const char* title,int top,int left, int width,int height);
	void Update();
	void Render();
	void Clean();
	void HandleEvents();
	inline bool IsRunning();

};

