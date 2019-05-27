#include "Camera.h"

GameObject* Camera::focus = nullptr;
Vec2d Camera::pos = Vec2d(0, 0);
Vec2d Camera::speed = Vec2d(0, 0);

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = nullptr;
}

void Camera::Update(float dt) {
	float speedamnt = 0.5;
	bool flag[2] = {false,false};
	if (focus != nullptr) {
		pos = Vec2d(focus->box.GetVecCentralizado() - Vec2d(1024, 600) / 2);
	}
	else {
		if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
			speed.x = -speedamnt;
			flag[0] = true;
		}
		if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
			speed.x = speedamnt;
			flag[0] = true;
		}
		if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
			speed.y = -speedamnt;
			flag[1] = true;
		}
		if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
			speed.y = speedamnt;
			flag[1] = true;
		}
		if(!flag[0]) {
			speed.x = 0;
		}
		if (!flag[1]) {
			speed.y = 0;
		}
		pos += speed * dt;
	}
}