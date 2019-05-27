#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"
#include "GameObject.h"
#include "Timer.h"
#include <cmath>
#include <iostream>
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

class Sprite : public Component{
public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
	~Sprite();
	void Open(string file);
	void SetClip(int x, int y, int w, int h);
	void Render();
	void Render(float x, float y, float w, float h);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
	void Update(float dt);
	bool Is(string type);
	void SetScale(float scaleX, float scaleY);
	Vec2d GetScale();
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
private:
	string file;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
	Vec2d scale;
	int frameCount, currentFrame;
	float timeElapsed, frameTime, secondsToSelfDestruct;
	Timer selfDestructCount;
};

#endif