#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "State.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Vec2d.h"
#include <memory>
#include <string>
#if defined (_WIN64) || defined (_WIN32)
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

using namespace std;

class StageState : public State {
public:
	StageState();
	~StageState();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void Start();
	void Pause();
	void Resume();
private:
	TileSet* tileSet;
	Music* backgroundMusic;
};

#endif