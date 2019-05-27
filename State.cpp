#include "State.h"

State::State() {
	quitRequested = false;
	popRequested = false;
	started = false;
}

State::~State() {
	objectArray.clear();
}

void State::Start() {
	LoadAssets();
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
}

bool State::PopRequested() {
	return popRequested;
}

bool State::QuitRequested() {
	return quitRequested;
}

weak_ptr<GameObject> State::AddObject(GameObject* go) {
	shared_ptr<GameObject> tmp(go);
	objectArray.emplace_back(tmp);
	if (!tmp->started) {
		tmp->Start();
	}
	return weak_ptr<GameObject>(tmp);
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	for (int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get() == go)
			return weak_ptr<GameObject>(objectArray[i]);
	}
	return weak_ptr<GameObject>();
}

void State::StartArray() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
}

void State::RenderArray() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}
}

void State::UpdateArray(float dt) {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
}