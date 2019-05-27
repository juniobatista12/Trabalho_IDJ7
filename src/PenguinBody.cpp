#include "PenguinBody.h"
#include "Alien.h"
#include "Bullet.h"
#include "Camera.h"
#include "Collider.h"
#include "Game.h"
#include "InputManager.h"
#include "PenguinCannon.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated){
	speed = Vec2d(0, 0);
	linearSpeed = 0;
	angle = 0;
	hp = 20;
	dead = false;
	player = this;
	associated.AddComponent(new Collider(associated));
	Camera::Follow(&associated);
}


PenguinBody::~PenguinBody() {
	player = nullptr;
}

void PenguinBody::Start() {
	auto penguinPass = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);
	GameObject* tmp = new GameObject();
	Sprite* sprite = new Sprite(*tmp, "assets/img/cubngun.png");
	tmp->box.h = sprite->GetHeight();
	tmp->box.w = sprite->GetWidth();
	tmp->box.SetCentro(associated.box.GetVecCentralizado());
	tmp->AddComponent(sprite);
	tmp->AddComponent(new PenguinCannon(*tmp, penguinPass));
	pcannon = Game::GetInstance().GetCurrentState().AddObject(tmp);
}

void PenguinBody::Update(float dt) {
	if (InputManager::GetInstance().IsKeyDown(W_KEY) && linearSpeed < MAXSPEED)
		linearSpeed += 0.01;
	else if (InputManager::GetInstance().IsKeyDown(S_KEY) && linearSpeed > -MAXSPEED)
		linearSpeed -= 0.01;
	if (InputManager::GetInstance().IsKeyDown(A_KEY))
		angle -= 0.001 * dt;
	else if (InputManager::GetInstance().IsKeyDown(D_KEY))
		angle += 0.001 * dt;
	speed = Vec2d(linearSpeed, 0).GetRotacao(angle);
	associated.angleDeg = (float)angle * 180 / PI;
	if (associated.box.GetVecCentralizado() + speed * dt < Vec2d(1408, 1280) && associated.box.GetVecCentralizado() + speed * dt > Vec2d(0, 0))
		associated.box.SetCentro(associated.box.GetVecCentralizado() + speed * dt);
	if (hp <= 0 && !dead) {
		Camera::Unfollow();
		associated.RemoveComponent("Sprite");
		auto cannon = pcannon.lock();
		cannon->RemoveComponent("Sprite");
		Sprite* sprite = new Sprite(associated, "assets/img/penguindeath.png", 5, 0.2, 1);
		associated.box.w = sprite->GetWidth();
		associated.box.h = sprite->GetHeight();
		associated.box.SetCentro(associated.box.GetVecCentralizado());
		associated.AddComponent(sprite);
		Sound* boom = new Sound(associated, "assets/audio/boom.wav");
		boom->Play();
		associated.AddComponent(boom);
		dead = true;
		linearSpeed = 0;
	}
}

void PenguinBody::Render(){}

bool PenguinBody::Is(string type) {
	return type == "PenguinBody";
}

void PenguinBody::NotifyCollision(GameObject& other) {
	Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
	if (bullet != nullptr && bullet->targetsPlayer) {
		hp -= bullet->GetDamage();
	}
	/*Alien* alien = (Alien*)other.GetComponent("Alien");
	if (alien != nullptr)
		linearSpeed = 0;*/
}