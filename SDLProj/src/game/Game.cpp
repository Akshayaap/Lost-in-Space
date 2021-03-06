#include <string>
#include <chrono>
#include "Game.h"
#include "..\sim\ObjInterface.h"

Game::Game(const char* title, int top, int left, int width, int height) 
	:ship(this->renderer, Vec2(200, 200), Vec2(2, 1)),
	earth(this->renderer, Vec2(500, 500), 20000, 20)
{
	Init(title, left, top, width, height);
	font = TTF_OpenFont("OpenSans-Regular.ttf", 50);

	ship.SetRenderer(this->renderer);
	earth.SetRenderer(this->renderer);
	
	this->slaves.push_back(ship.GetSlave());
	
	this->slaves.push_back(earth.GetSlave());

	InitPath();
	//maze = Maze(this->renderer);
}

Game::~Game() {
	Clean();
}

void Game::Go() {

	 int frames = 0;
    double unprocessedSeconds = 0;
    double previousTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    double secondsForEachTick = 1/60.0; 


    int tickCount = 0; //RENDER COUNTER
    bool ticked = false;

    while (isRunning) 
    {
        double currentTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        double passedTime = currentTime - previousTime;

        previousTime = currentTime;

        unprocessedSeconds = unprocessedSeconds + passedTime / 1000000000.0;

        int count = 0;
        while(unprocessedSeconds > secondsForEachTick)
		{
			HandleEvents();
            Update();
            count++;
            unprocessedSeconds -= secondsForEachTick; 

            ticked = true;
            tickCount++;

            if(tickCount % 60 == 0){
                previousTime += 1;
                frames = 0;
            }
        }
        if(ticked)
        {
            Render();
            frames++;
            ticked = false;
        }

    }
}


void Game::Init(const char* title, int top, int left, int width, int height) {
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init()==0) {
		LOG("Subsystem Initialized");

		window = SDL_CreateWindow(title, left, top, width, height, SDL_WINDOW_FULLSCREEN);
		if (window) {
			LOG("Window Created");
		}

		for (int i = 0; i < SDL_GetNumRenderDrivers(); ++i){
			SDL_RendererInfo info = {};
			SDL_GetRenderDriverInfo(i, &info);
			LOG(info.name);
			if (info.name != std::string("direct3d11")){
				continue;
			}
			renderer = SDL_CreateRenderer(window, i, 0);
			LOG("Just to make sure that Renderer initialize with Direct3D11 backend");
			break;
		}
		if (renderer) {
			LOG("Renderer is Created Successfully");
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
}

void Game::Update() {

#ifndef NDEBUG
	static int ticked = 0;
	static int count = 0;
	count++;
	if (count >= 60) {
		ticked++;
		LOG("Update -------------------> : " << ticked);
		count = 0;
	}
#endif // !NDEBUG

	Interact();
	ship.Update();
	earth.Update();
	//for (auto& slave : this->slaves) {
		//slave->Update();
	//}
	
	/*
	if (maze.IsWinning(ship)) {
		state.SetGameState(State::GAME_WON);
		state.SetMessageState(State::MESSAGE_HIT_GATE);
	}
	if (maze.IsHitting(ship)) {
		state.SetGameState(State::GAME_OVER);
		state.SetMessageState(State::MESSAGE_HIT_WALL);
	}*/
}

void Game::Render() {
	//LOG("Render");


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//this->maze.Render();
	earth.Render();
	this->ship.Render();
	for (auto& slave: this->slaves) {
		slave->Render();
	}
	LOG("SDL Error:" << SDL_GetError());

	if (state.GetMessageState() != State::NORMAL) {
		SDL_Surface* surface = nullptr;
		const char* msg = nullptr;
		SDL_Color color = { 0, };

		switch (state.GetMessageState()) {

		case State::MESSAGE_HIT_GATE:
			msg = "YOU WON";
			color = { 0,255,0,255 };
			break;

		case State::MESSAGE_HIT_WALL:
			msg = "GAME OVER";
			color = { 255,0,0,255 };
			break;

		default:
			LOG("INVALID state");
			surface = nullptr;
			return;
			break;
		}
		
		surface = TTF_RenderText_Solid(font, msg,color );
		message = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_Rect mRect;
		mRect.x = 500;
		mRect.y = 300;
		mRect.w = 400;
		mRect.h = 100;

		SDL_RenderCopy(renderer, message, nullptr, &mRect);
		if (surface) {
			SDL_FreeSurface(surface);
		}
	}
	SDL_RenderPresent(renderer);
	PostProcessing();
}

void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	LOG("SDL is destroyed");
}

void Game::HandleEvents() {
	SDL_Event event;
	int x = 0, y = 0;
	while (SDL_PollEvent(&event)) {
		//LOG("Event:" << event.type);

		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			//LOG("Event::SDL_QUIT");
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == 1) {
				state.SetMouseState(State::MOUSE_LEFT_DOWN);
				InitPath();
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == 1) {
				state.SetMouseState(State::MOUSE_LEFT_UP);
				InitPath();
			}
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				this->ship.Accelerate(0.01);
				break;

			case SDLK_DOWN:
				this->ship.Accelerate(-0.01);
				break;

			case SDLK_LEFT:
				this->ship.RollLeft();
				break;

			case SDLK_RIGHT:
				this->ship.RollRight();
				break;

			case SDLK_8:
				this->ship.Accelerate(1);
				break;

			case SDLK_4:
				break;

			case SDLK_6:
				break;

			case SDLK_2:
				this->ship.Accelerate(-1);
				break;

			case SDLK_5:
				break;

			default:
				break;
			}
			InitPath();
			break;
		
		case SDL_MOUSEWHEEL:

			SDL_GetMouseState(&x,&y);
			LOG("X:" << x << "\tY:" << y);

			ship.Scal(event.wheel.y , Vec2(x, y));
			earth.Scal(event.wheel.y , Vec2(x, y));\
			InitPath();
			break;
		case SDL_MOUSEMOTION:
			switch (state.GetMouseState()) {
			case State::MOUSE_LEFT_DOWN:
				ship.Translate(Vec2(event.motion.xrel, event.motion.yrel));
				earth.Translate(Vec2(event.motion.xrel, event.motion.yrel));
				InitPath();
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
	
}

void Game::Reset() {
	ship.Reset();
	ship.SetPos(Vec2(100, 100));
	state.SetGameState(State::NORMAL);
	state.SetMouseState(State::NORMAL);
	state.SetMessageState(State::NORMAL);
}

void Game::PostProcessing() {
	switch (state.GetGameState())
	{
	case State::GAME_WON:
	case State::GAME_OVER:
		SDL_Delay(2000);
		Reset();
		SDL_PumpEvents();
		SDL_FlushEvents(0,INT_MAX);
		break;
	default:
		break;
	}
}

void Game::Interact() {
	earth.Interact(ship);
	ship.Interact(earth);
	for (int j = 0; j < this->slaves.size(); j++) {
		for (int k = 0; k < this->slaves.size(); k++) {
			if (j != k) {
				this->slaves[j]->Interact(*this->slaves[k]);
			}
		}
		this->slaves[j]->Update();
	}
}

void Game::InitPath() {
	for (int i = 0; i < this->slaves.size(); i++) {
		this->slaves[i]->Clear();
		this->slaves[i]->Reset();
	}
	for (int i = 0; i < PATH_LENGTH; i++) {
		for (int j = 0; j < this->slaves.size(); j++) {
			for (int k = 0; k < this->slaves.size(); k++) {
				if (j != k) {
					this->slaves[j]->Interact(*this->slaves[k]);
				}
			}
			this->slaves[j]->Update();
		}
	}
}