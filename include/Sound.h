#ifndef SOUND_H
#define SOUND_H

#include "Component.h"
#include "GameObject.h"
#include <iostream>
#include <string>
#if defined (_WIN64) || defined (_WIN32)
	#include <SDL_mixer.h>
#else
	#include <SDL2/SDL_mixer.h>
#endif

using namespace std;

class Sound : public Component{
public:
    Sound (GameObject& associated);
    Sound (GameObject& associated, string file);
    ~Sound();
	bool IsPlaying();
    void Play(int times = 0);
    void Stop();
    void Open(string file);
    bool IsOpen();
    void Update(float dt);
    void Render();
    bool Is(string type);
    int channel;
private:
    Mix_Chunk* chunk;
};

#endif