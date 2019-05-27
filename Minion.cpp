#include "Minion.h"
#include"Collider.h"
#include "Game.h"
#include "Bullet.h"
Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter) {
	arc = arcOffsetDeg;
	associated.AddComponent(new Collider(associated));
}

void Minion::Update(float dt) {
	auto a = alienCenter.lock();
	if (a == nullptr) {
		associated.RequestDelete();
	}
	else {
		Vec2d pos = Vec2d(150, 0);
		float f = 0.1;
		pos = pos.GetRotacao(arc);
		pos += a->box.GetVecCentralizado();
		associated.box.SetCentro(pos);
		associated.angleDeg = arc * 180 / PI - 90;
		arc += 2 * PI * f * dt / 1000;
		if (arc > 2 * PI)
			arc -= 2 * PI;
	}
}

void Minion::Render() {}

bool Minion::Is(string type) {
	return type == "Minion";
}

void Minion::Shoot(Vec2d pos) {
	Vec2d direcao = pos - associated.box.GetVecCentralizado();
	GameObject* tmp = new GameObject();
	tmp->box.SetCentro(associated.box.GetVecCentralizado());
	Bullet* bullet = new Bullet(*tmp, direcao.GetInclinacao(), 0.1, 10, 1000, "assets/img/minionbullet2.png", true);
	tmp->AddComponent(bullet);
	Game::GetInstance().GetCurrentState().AddObject(tmp);
}