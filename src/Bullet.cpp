#include "Bullet.h"
#include "Collider.h"
#include "PenguinBody.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, bool targetsPlayer, int frameCount) : Component(associated) {
	Vec2d speedtmp = Vec2d(speed, 0);
	associated.angleDeg = angle * 180 / PI;
	this->speed = speedtmp.GetRotacao(angle);
	this->targetsPlayer = targetsPlayer;
	distanceLeft = maxDistance;
	this->damage = damage;
	Sprite * spritetmp = new Sprite(associated, sprite, frameCount);
	associated.box.w = spritetmp->GetWidth();
	associated.box.h = spritetmp->GetHeight();
	associated.AddComponent(spritetmp);
	associated.AddComponent(new Collider(associated));
	associated.box.SetCentro(associated.box.GetVecCentralizado() + Vec2d(125, 0).GetRotacao(angle));
}

void Bullet::Update(float dt) {
	Vec2d distPercorrida;
	associated.box.SetCentro(associated.box.GetVecCentralizado() + speed * dt);
	distPercorrida = Vec2d(speed * dt);
	distanceLeft -= distPercorrida.GetMagnitude();
	if (distanceLeft <= 0) {
		associated.RequestDelete();
	}
}

void Bullet::Render() {}

bool Bullet::Is(string type) {
	return type == "Bullet";
}

int Bullet::GetDamage() {
	return damage;
}

void Bullet::NotifyCollision(GameObject& other) {
	Bullet* pb = (Bullet*)other.GetComponent("Bullet");
	if (pb == nullptr) {
		associated.RequestDelete();
	}
}