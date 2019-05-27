#ifndef MINION_H
#define MINION_H

#include "Component.h"

class Minion : public Component{
public:
	Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
	void Update(float dt);
	void Render();
	bool Is(string type);
	void Shoot(Vec2d target);
private:
	weak_ptr<GameObject> alienCenter;
	float arc;
};

#endif