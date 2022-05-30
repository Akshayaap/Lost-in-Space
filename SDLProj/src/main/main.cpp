
#include "..\game\Game.h"

#ifndef NDEBUG
#include <iostream>
#define LOG(msg) std::cout<<__FILE__<<":"<<__LINE__<<"::"<<msg<<std::endl
#else
#define LOG(msg)
#include <Windows.h>
#endif // !NDEBUG



#ifndef NDEBUG
int main(int argc, char** argv) 
#else
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#endif // !NDEBUG

{

	Game game("Start wars", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080);
	game.Go();

	return 0;
}