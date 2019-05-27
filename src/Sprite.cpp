#include "Sprite.h"
#include "Camera.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite(GameObject& associated) : Component(associated){
	texture = nullptr;
	scale = Vec2d(1, 1);
}

Sprite::Sprite(GameObject& associated, string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated){
	texture = nullptr;
	Open(file);
	SetClip(0, 0, width, height);
	scale = Vec2d(1, 1);
	this->secondsToSelfDestruct = secondsToSelfDestruct;
	selfDestructCount = Timer();
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	this->currentFrame = 0;
	this->timeElapsed = 0;
}

Sprite::~Sprite(){
	/*if (texture!=nullptr) {
		SDL_DestroyTexture(texture);
	}*/
}

void Sprite::Open(string file) {
	texture = Resources::GetImage(file);
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	this->file = file;
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render() {
	SDL_Rect dstRect;
	dstRect.x = associated.box.x - Camera::pos.x;
	dstRect.y = associated.box.y - Camera::pos.y;
	dstRect.h = GetHeight();
	dstRect.w = GetWidth();
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
	//cout << "Rendering file: " << file << endl;
}

void Sprite::Render(float x, float y, float w, float h){
	SDL_Rect dstRect;
	dstRect.x = nearbyint(x);
	dstRect.y = nearbyint(y);
	dstRect.h = nearbyint(h);
	dstRect.w = nearbyint(w);
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
	//cout << "Rendering file: " << file << endl;
}

int Sprite::GetWidth() {
	return width / frameCount * scale.x;
}

int Sprite::GetHeight() {
	return height * scale.y;
}

bool Sprite::IsOpen() {
	return texture == nullptr ? false : true;
}

void Sprite::Update(float dt){
	timeElapsed += dt;
	selfDestructCount.Update(dt);
	if (timeElapsed > frameTime) {
		timeElapsed = 0;
		currentFrame++;
		if (currentFrame > frameCount - 1) {
			currentFrame = 0;
		}
		SetFrame(currentFrame);
	}
	if (secondsToSelfDestruct && secondsToSelfDestruct < selfDestructCount.Get()) {
		associated.RequestDelete();
	}
}

bool Sprite::Is(string type){
	return type == "Sprite" ? true : false;
}

void Sprite::SetScale(float scaleX, float scaleY) {
	scale = Vec2d(scaleX, scaleY);
	Vec2d Centro = associated.box.GetVecCentralizado();
	associated.box.x *= scale.x;
	associated.box.y *= scale.y;
	associated.box.SetCentro(Centro);
}

void Sprite::SetFrame(int frame) {
	int x = frame * GetWidth();
	int y = 0;
	int w = GetWidth();
	int h = GetHeight();
	SetClip(x, y, w, h);
}

void Sprite::SetFrameCount(int frameCount) {
	this->frameCount = frameCount;
}

void Sprite::SetFrameTime(float frameTime) {
	this->frameTime = frameTime;
}