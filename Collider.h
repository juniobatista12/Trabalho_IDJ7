#pragma once
#include "Camera.h"
#include "Game.h"
#if (defined (_WIN64) || defined (_WIN32)) && defined(_DEBUG)
#include <SDL.h>
#elif defined (DEBUG) && !(defined(_WIN64) || defined(_WIN32))
#include <SDL2/SDL.h>
#endif


#include "Component.h"
class Collider : public Component {
public:
	Collider(GameObject& associated, Vec2d scale = { 1,1 }, Vec2d offset = { 0,0 });
	Rect box;
	void Update(float dt);
	void Render();
	bool Is(string type);
	void SetScale(Vec2d scale);
	void SetOffset(Vec2d offset);
private:
	Vec2d scale, offset;
};

