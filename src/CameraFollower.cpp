#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go) {
	
}

void CameraFollower::Update(float dt) {
	associated.box.SetCentro(Camera::pos + Vec2d(1024, 600) / 2);
}

void CameraFollower::Render() {
}

bool CameraFollower::Is(string type) {
	return type == "CameraFollower";
}