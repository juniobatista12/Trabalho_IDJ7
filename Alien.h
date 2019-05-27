#ifndef ALIEN_H
#define ALIEN_H

#include "GameObject.h"
#include "Minion.h"
#include "Sprite.h"
#include <queue>

class Alien : public Component{
public:
	Alien(GameObject& associated, int nMinions, float secondsCD = 5);
	~Alien();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
	static int alienCount;
private:
	enum AlienState { MOVING, RESTING };
	AlienState state;
	Timer restTimer;
	Vec2d destination;
	Vec2d speed;
	float hp;
	float secondsCD;
	bool dead;
	int nMinions;
	vector<weak_ptr<GameObject>> minionArray;
};

#endif