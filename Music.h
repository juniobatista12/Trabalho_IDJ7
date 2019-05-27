#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <string>
#if defined (_WIN64) || defined (_WIN32)
	#include <SDL_mixer.h>
#else
	#include <SDL2/SDL_mixer.h>
#endif

using namespace std;

class Music
{
public:
	Music();
	Music(string file);
	void Play(int playtimes = -1);
	void Stop(int msToStop = 1500);
	void Open(string file);
	bool IsOpen();
	~Music();
private:
	Mix_Music* music;
};

#endif