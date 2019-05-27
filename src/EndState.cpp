#include "EndState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Sprite.h"
#include "TitleState.h"

EndState::EndState() {
	if (GameData::playerVictory) {
		GameObject* bg = new GameObject();
		Sprite* sprite = new Sprite(*bg, "assets/img/win.jpg");
		bg->box = Rect(0, 0, sprite->GetWidth(), sprite->GetHeight());
		bg->AddComponent(sprite);
		objectArray.emplace_back(bg);
		backgroundMusic = Music("assets/audio/endStateWin.ogg");
		backgroundMusic.Play();
	}
	else {
		GameObject* bg = new GameObject();
		Sprite* sprite = new Sprite(*bg, "assets/img/lose.jpg");
		bg->box = Rect(0, 0, sprite->GetWidth(), sprite->GetHeight());
		bg->AddComponent(sprite);
		objectArray.emplace_back(bg);
		backgroundMusic = Music("assets/audio/endStateLose.ogg");
		backgroundMusic.Play();
	}
}

void EndState::Update(float dt) {
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	else if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		popRequested = true;
		TitleState* titleState = new TitleState();
		Game::GetInstance().Push(titleState);
	}
}

void EndState::Render() {
	RenderArray();
}

void EndState::LoadAssets(){}

void EndState::Start() {
}

void EndState::Pause() {
	backgroundMusic.Stop(0);
}

void EndState::Resume() {}