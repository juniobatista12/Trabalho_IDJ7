#include "Sound.h"
#include "Resources.h"

Sound::Sound (GameObject& associated) : Component(associated){
    this->associated = associated;
    chunk = nullptr;
}

Sound::Sound (GameObject& associated, string file) : Component(associated){
    this->associated = associated;
    Open(file);
}

Sound::~Sound(){
    //while(Mix_Playing(channel));
    if(chunk!=nullptr){
        Mix_HaltChannel(channel);
    }
}

bool Sound::IsPlaying() {
	return Mix_Playing(channel);
}

void Sound::Play(int times){
    channel=Mix_PlayChannel(-1, chunk, times);
}

void Sound::Stop(){
    Mix_HaltChannel(channel);
}

void Sound::Open(std::string file){
    chunk=Resources::GetSound(file);
}

void Sound::Update(float dt){

}

void Sound::Render(){

}

bool Sound::Is(string type){
    return type == "Sound" ? true : false;
}