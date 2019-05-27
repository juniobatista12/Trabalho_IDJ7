#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Sprite.h"

class Bullet : public Component {
public:
	Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, bool targetsPlayer, int frameCount = 3);
	void Update(float dt);
	void Render();
	bool Is(string type);
	int GetDamage();
	void NotifyCollision(GameObject& other);
	bool targetsPlayer;
private:
	Vec2d speed;
	float distanceLeft;
	int damage;
};

#endif