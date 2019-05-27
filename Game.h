#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "StageState.h"
#include <iostream>
#include <stack>
#include <string>
#if defined (_WIN64) || defined (_WIN32)
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_mixer.h>
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_mixer.h>
#endif

using namespace std;

class Game {
public:
	~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	void Push(State* state);
	static Game& GetInstance();
	State& GetCurrentState();
	float GetDeltaTime();
private:
	Game(string title, int width, int height);
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* storedState;
	int frameStart;
	float dt;
	void CalculateDeltaTime();
	stack<unique_ptr<State>> stateStack;
};

#endif