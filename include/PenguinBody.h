#ifndef PENGUINBODY_H
#define PENGUINBODY_H
#define MAXSPEED 0.25
#include "Component.h"

class PenguinBody : public Component{
public:
	PenguinBody(GameObject& associated);
	~PenguinBody();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
	static PenguinBody* player;
private:
	weak_ptr<GameObject> pcannon;
	Vec2d speed;
	bool dead;
	float linearSpeed;
	float angle;
	int hp;
};

#endif