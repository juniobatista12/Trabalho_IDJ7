#include "PenguinCannon.h"
#include "Bullet.h"
#include "Camera.h"
#include "Collider.h"
#include "Game.h"
#include "InputManager.h"
#include "PenguinBody.h"

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody) : Component(associated) {
	pbody = penguinBody;
	associated.AddComponent(new Collider(associated));
	timer = Timer(5);
}

void PenguinCannon::Update(float dt) {
	if (pbody.lock() == nullptr) {
		associated.RequestDelete();
	}
	else {
		auto& p = *pbody.lock();
		associated.box.SetCentro(p.box.GetVecCentralizado());
		Vec2d mousePos(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
		angle = (mousePos + Camera::pos - associated.box.GetVecCentralizado()).GetInclinacao();
		associated.angleDeg = angle * 180 / PI;
		timer.Update(dt);
		if (timer.Get() > 1) {
			if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
				Shoot();
				timer.Restart();
			}
		}
	}
}

void PenguinCannon::Shoot() {
	GameObject* tmp = new GameObject();
	tmp->box.SetCentro(associated.box.GetVecCentralizado());
	Bullet* bullet = new Bullet(*tmp, angle, 0.5, 10, 1000, "assets/img/penguinbullet.png", false, 4);
	tmp->AddComponent(bullet);
	Game::GetInstance().GetCurrentState().AddObject(tmp);
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(string type) {
	return type == "PenguinCannon";
}

void PenguinCannon::NotifyCollision(GameObject& other) {
	/*Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
	if (bullet) {
		PenguinBody::player->NotifyCollision(other);
	}*/
}