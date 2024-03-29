#include "Alien.h"
#include <float.h>
#include "Bullet.h"
#include "Camera.h"
#include "Collider.h"
#include "InputManager.h"
#include "Game.h"
#include "State.h"
#include "Sound.h"
#include "PenguinBody.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions, float secondsCD) : Component(associated) {
	Sprite* sprite = new Sprite(associated, "assets/img/alien.png");
	associated.box.h = sprite->GetHeight();
	associated.box.w = sprite->GetWidth();
	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
	this->nMinions = nMinions;
	hp = 30;
	speed = Vec2d(0, 0);
	alienCount++;
	state = RESTING;
	dead = false;
	this->secondsCD = secondsCD;
}

Alien::~Alien() {
	minionArray.clear();
	alienCount--;
}

void Alien::Start() {
	auto alienPass = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);
	for (int i = 0; i < nMinions; i++) {
		GameObject* tmp = new GameObject();
		Sprite* sprite = new Sprite(*tmp, "assets/img/minion.png");
		float scale = (rand() % 6 + 10) / 10.0;
		sprite->SetScale(scale, scale);
		tmp->box.w = sprite->GetWidth();
		tmp->box.h = sprite->GetHeight();
		tmp->box.x = associated.box.x;
		tmp->box.y = associated.box.y;
		tmp->AddComponent(sprite);
		tmp->AddComponent(new Minion(*tmp, alienPass, i * 2 * PI / nMinions));
		minionArray.push_back(Game::GetInstance().GetCurrentState().AddObject(tmp));
	}
}

void Alien::Update(float dt) {
	if (state == RESTING) {
		restTimer.Update(dt);
		if (restTimer.Get() > secondsCD) {
			if (PenguinBody::player != nullptr) {
				destination = PenguinBody::player->associated.box.GetVecCentralizado();
				speed = (destination - associated.box.GetVecCentralizado()).GetNormalizado();
				speed *= 0.5;
				state = MOVING;
			}
		}
	}
	if (state == MOVING) {
		associated.box.SetCentro(associated.box.GetVecCentralizado() + speed * dt);
		if ((associated.box.GetVecCentralizado() - destination).GetMagnitude() < dt) {
			destination = PenguinBody::player->associated.box.GetVecCentralizado();
			Minion* selected = nullptr;
			float min = FLT_MAX;
			for (unsigned int i = 0; i < minionArray.size(); i++) {
				shared_ptr<GameObject> tmp = minionArray[i].lock();
				float dist = (tmp->box.GetVecCentralizado() - destination).GetMagnitude();
				if (dist < min) {
					selected = (Minion*)tmp->GetComponent("Minion");
					min = dist;
				}
			}
			selected->Shoot(PenguinBody::player->associated.box.GetVecCentralizado());
			state = RESTING;
			restTimer.Restart();
		}
	}
	if (hp <= 0 && !dead) {
		associated.RemoveComponent("Sprite");
		Sprite* sprite = new Sprite(associated, "assets/img/aliendeath.png", 4, 0.25, 1.25);
		associated.box.w = sprite->GetWidth();
		associated.box.h = sprite->GetHeight();
		associated.box.SetCentro(associated.box.GetVecCentralizado());
		associated.AddComponent(sprite);
		Sound * boom = new Sound(associated, "assets/audio/boom.wav");
		boom->Play();
		for (unsigned int i = 0; i < minionArray.size(); i++) {
			auto minion = minionArray[i].lock();
			Sprite* minionsprite = new Sprite(*minion, "assets/img/miniondeath.png", 4, 0.25, 1);
			minion->box.w = minionsprite->GetWidth();
			minion->box.h = minionsprite->GetHeight();
			minion->RemoveComponent("Sprite");
			minion->AddComponent(minionsprite);
		}
		associated.AddComponent(boom);
		dead = true;
	}
	associated.angleDeg -= (2 * PI * 0.05 * dt / 1000) * 180 / PI;
	if (associated.angleDeg < 0) {
		associated.angleDeg += 360;
	}
}

void Alien::Render() {}

bool Alien::Is(string type) {
	return type == "Alien";
}

void Alien::NotifyCollision(GameObject & other) {
	Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
	if (bullet != nullptr && !bullet->targetsPlayer) {
		hp -= bullet->GetDamage();
	}
}