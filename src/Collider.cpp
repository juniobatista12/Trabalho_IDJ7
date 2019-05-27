#include "Collider.h"



Collider::Collider(GameObject& associated, Vec2d scale, Vec2d offset) : Component(associated) {
	this->scale = scale;
	this->offset = offset;
}


void Collider::Update(float dt) {
	box.h = associated.box.h * scale.y;
	box.w = associated.box.w * scale.x;
	box.SetCentro(associated.box.GetVecCentralizado() + offset);
}

void Collider::Render() {
#if defined(DEBUG) || defined (_DEBUG)
	Vec2d center(box.GetVecCentralizado());
	SDL_Point points[5];

	Vec2d point = (Vec2d(box.x, box.y) - center).GetRotacao(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[0] = { (int)point.x, (int)point.y };
	points[4] = { (int)point.x, (int)point.y };

	point = (Vec2d(box.x + box.w, box.y) - center).GetRotacao(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[1] = { (int)point.x, (int)point.y };

	point = (Vec2d(box.x + box.w, box.y + box.h) - center).GetRotacao(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[2] = { (int)point.x, (int)point.y };

	point = (Vec2d(box.x, box.y + box.h) - center).GetRotacao(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[3] = { (int)point.x, (int)point.y };

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif
}

bool Collider::Is(string type) {
	return type == "Collider";
}

void Collider::SetOffset(Vec2d offset) {
	this->offset = offset;
}

void Collider::SetScale(Vec2d scale) {
	this->scale = scale;
}