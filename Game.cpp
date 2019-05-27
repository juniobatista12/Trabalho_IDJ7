#include "Game.h"
#include "InputManager.h"
#include "Resources.h"
#include <SDL_ttf.h>

Game* Game::instance = nullptr;

Game::Game(string title, int width, int height) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		cerr << SDL_GetError();
		exit(-1);
	}
	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
		cerr << SDL_GetError();
		exit(-1);
	}
	if (!Mix_Init(MIX_INIT_OGG)) {
		cerr << SDL_GetError();
		exit(-1);
	}
	if (TTF_Init()) {
		cerr << SDL_GetError();
		exit(-1);
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
		cerr << SDL_GetError();
		exit(-1);
	}
	Mix_AllocateChannels(32);
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (window == nullptr) {
		cerr << SDL_GetError();
		exit(-1);
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		cerr << SDL_GetError();
		exit(-1);
	}
	frameStart = SDL_GetTicks();
	storedState = nullptr;
}


Game::~Game() {
	if (storedState != nullptr) {
		delete(storedState);
	}
	do {
		stateStack.pop();
	} while (!stateStack.empty());
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Game& Game::GetInstance() {

	if (instance == nullptr) {
		instance = new Game("Divino Junio Batista Lopes - 150033443", 1024, 600);
	}
	return *instance;
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

State& Game::GetCurrentState() {
	return *stateStack.top();
}

void Game::Push(State* state) {
	storedState = state;
}

void Game::Run() {
	if (storedState != nullptr) {
		stateStack.emplace(storedState);
		stateStack.top()->Start();
		storedState = nullptr;
	}
	else
		exit(0);
	while (!stateStack.top()->QuitRequested() && !stateStack.empty()) {
		if (stateStack.top()->PopRequested()) {
			stateStack.top()->Pause();
			stateStack.pop();
			if (stateStack.size())
				stateStack.top()->Resume();
		}
		if (storedState != nullptr) {
			stateStack.top()->Pause();
			stateStack.emplace(storedState);
			stateStack.top()->Start();
			storedState = nullptr;
		}
		CalculateDeltaTime();
		InputManager::GetInstance().Update();
		stateStack.top()->Update(dt);
		stateStack.top()->Render();
		SDL_RenderPresent(Game::GetInstance().GetRenderer());
		//cout << boolalpha << stateStack.top()->QuitRequested() << endl;
	}
}

void Game::CalculateDeltaTime() {
	dt = (SDL_GetTicks() - frameStart);
	frameStart = SDL_GetTicks();
}

float Game::GetDeltaTime() {
	return dt;
}