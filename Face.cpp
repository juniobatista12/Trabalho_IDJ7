#include "Face.h"
#include "Camera.h"
#include "InputManager.h"
#include "Sprite.h"

Face::Face(GameObject& associated) : Component(associated) {
	hitpoints = 30;
	played = false;
	requestDelete = false;
}

Face::~Face() {}

void Face::Damage(int damage) {
	hitpoints -= damage;
	if (hitpoints <= 0) {
		Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
		associated.RemoveComponent(sprite);
		sound = (Sound*)associated.GetComponent("Sound");
		if (sound != nullptr && !played) {
			sound->Play();
			played=true;
		}
	}
}

void Face::Update(float dt) {
	if (InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON) && associated.box.Contains(InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y)) {
		Damage(rand() % 10 + 10);
	}
	if (!sound->IsPlaying() && played) {
		associated.RequestDelete();
	}
}

void Face::Render() {

}

bool Face::Is(string type) {
	return type == "Face" ? true : false;
}