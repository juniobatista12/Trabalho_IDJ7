#pragma once
#include "Component.h"
#include "Timer.h"
class PenguinCannon : public Component {
public:
	PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody);
	void Update(float dt);
	void Render();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
	void Shoot();
private:
	weak_ptr<GameObject> pbody;
	float angle;
	Timer timer;
};

