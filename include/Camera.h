#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "InputManager.h"
#include "Vec2d.h"

class Camera {
public:
	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);
	static Vec2d pos, speed;
private:
	static GameObject* focus;
};

#endif