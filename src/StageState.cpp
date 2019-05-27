#include "StageState.h"
#include "Alien.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Collider.h"
#include "Collision.h"
#include "EndState.h"
#include "GameData.h"
#include "InputManager.h"
#include "PenguinBody.h"
#include "Resources.h"

StageState::StageState() {
	backgroundMusic = nullptr;
	quitRequested = false;
	started = false;
	tileSet = nullptr;
}

StageState::~StageState() {
	objectArray.clear();
}

void StageState::LoadAssets() {
	GameObject* background = new GameObject();
	Sprite* bg = new Sprite(*background, "assets/img/ocean.jpg");
	background->box.x = 0;
	background->box.y = 0;
	background->box.h = bg->GetHeight();
	background->box.w = bg->GetWidth();
	background->AddComponent(bg);
	background->AddComponent(new CameraFollower(*background));
	objectArray.emplace_back(background);
	GameObject* tileMap = new GameObject();
	tileSet = new TileSet(*tileMap, 64, 64, "assets/img/tileset.png");
	TileMap* tm = new TileMap(*tileMap, "assets/map/tileMap.txt", tileSet);
	tileMap->AddComponent(tm);
	objectArray.emplace_back(tileMap);
	GameObject* alien1 = new GameObject();
	alien1->AddComponent(new Alien(*alien1, 3));
	alien1->box.SetCentro(512, 300);
	objectArray.emplace_back(alien1);
	GameObject* alien2 = new GameObject();
	alien2->AddComponent(new Alien(*alien2, 3, 2));
	alien2->box.SetCentro(100, 100);
	objectArray.emplace_back(alien2);
	GameObject* penguin = new GameObject();
	Sprite* penguinsprite = new Sprite(*penguin, "assets/img/penguin.png");
	penguin->box.SetCentro(704, 640);
	penguin->box.h = penguinsprite->GetHeight();
	penguin->box.w = penguinsprite->GetWidth();
	penguin->AddComponent(penguinsprite);
	penguin->AddComponent(new PenguinBody(*penguin));
	objectArray.emplace_back(penguin);
	backgroundMusic = new Music("assets/audio/stageState.ogg");
	backgroundMusic->Play();
}

void StageState::Update(float dt) {
	quitRequested = false;
	Camera::Update(dt);
	// Se o evento for quit, setar a flag para terminação
	if (InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}

	// Se o evento for clique...
	else if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		popRequested = true;
		Camera::Unfollow();
		Camera::pos = { 0,0 };
	}
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		Collider* a = (Collider*)objectArray[i]->GetComponent("Collider");
		if (a != nullptr) {
			for (unsigned int j = i + 1; j < objectArray.size(); j++) {
				Collider* b = (Collider*)objectArray[j]->GetComponent("Collider");
				if (b != nullptr) {
					if (Collision::IsColliding(a->box, b->box, a->associated.angleDeg, b->associated.angleDeg)) {
						objectArray[i]->NotifyCollision(*objectArray[j]);
						objectArray[j]->NotifyCollision(*objectArray[i]);
					}
				}
			}
		}
	}
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
			i--;
		}
	}
	bool achou = false;
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		PenguinBody* pb = (PenguinBody*)objectArray[i]->GetComponent("PenguinBody");
		if (pb != nullptr) {
			achou = true;
		}
	}
	if (!achou) {
		Camera::Unfollow();
		Camera::pos = Vec2d(0, 0);
		popRequested = true;
		GameData::playerVictory = false;
		EndState* endState = new EndState();
		Game::GetInstance().Push(endState);
	}
	if (!Alien::alienCount) {
		Camera::Unfollow();
		Camera::pos = Vec2d(0, 0);
		popRequested = true;
		GameData::playerVictory = true;
		EndState* endState = new EndState();
		Game::GetInstance().Push(endState);
	}

}

void StageState::Render() {
	TileMap* tm1 = nullptr;
	TileMap* tm = nullptr;
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		tm1 = (TileMap*)objectArray[i]->GetComponent("TileMap");
		if (tm1 != nullptr) {
			tm = tm1;
			tm->RenderLayer(0, Camera::pos.x, Camera::pos.y);
		}
		else
			objectArray[i]->Render();
	}
	if (tm != nullptr) {
		tm->RenderLayer(1, Camera::pos.x, Camera::pos.y);
	}
}

void StageState::Start() {
	LoadAssets();
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
}

void StageState::Resume() {

}

void StageState::Pause() {
}