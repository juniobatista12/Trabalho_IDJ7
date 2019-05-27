#include "TitleState.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Text.h"
#include "StageState.h"

TitleState::TitleState() {
	GameObject* gobgsprite = new GameObject();
	Sprite* sprite = new Sprite(*gobgsprite, "assets/img/title.jpg");
	gobgsprite->box = Rect(0, 0, sprite->GetWidth(), sprite->GetHeight());
	gobgsprite->AddComponent(sprite);
	objectArray.emplace_back(gobgsprite);
	GameObject* gofont = new GameObject();
	gofont->box = Rect(0, 0, 0, 0);
	Text* text = new Text(*gofont, "assets/font/Call me maybe.ttf", 60, Text::TextStyle::BLENDED, "Aperte espaco para comecar", SDL_Color{ 255,165,0 });
	gofont->AddComponent(text);
	gofont->box.SetCentro(1024 / 2, 560);
	objectArray.emplace_back(gofont);
	timer = Timer();
	texten = true;
}

TitleState::~TitleState() {}

void TitleState::LoadAssets() {}

void TitleState::Update(float dt) {
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}
	else if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		Game::GetInstance().Push(new StageState());
	}
	if (texten && timer.Get() > 1) {
		Text* text = (Text*)objectArray[1]->GetComponent("Text");
		if (text != nullptr) {
			text->SetColor(SDL_Color{ 0xFF,0xFF,0xFF });
			texten = false;
			timer.Restart();
		}
	}
	else if (!texten && timer.Get() > 1) {
		Text* text = (Text*)objectArray[1]->GetComponent("Text");
		if (text != nullptr) {
			text->SetColor(SDL_Color{ 255,165,0 });
			texten = true;
			timer.Restart();
		}
	}
	timer.Update(dt);
}

void TitleState::Render() {
	RenderArray();
}

void TitleState::Start() {
	StartArray();
}

void TitleState::Pause() {}

void TitleState::Resume() {}