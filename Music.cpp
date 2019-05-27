#include "Music.h"
#include "Resources.h"

Music::Music() : music(nullptr) {
}

Music::Music(string file) {
	Open(file);
}

Music::~Music() {
	//Mix_FreeMusic(music);
}

void Music::Play(int playtimes) {
	Mix_PlayMusic(music, playtimes);
	if (music == nullptr) {
		cerr << SDL_GetError();
		exit(-1);
	}
}

void Music::Stop(int msToStop) {
	Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
	music = Resources::GetMusic(file);
}

bool Music::IsOpen() {
	return music == nullptr ? false : true;
}