#ifndef FACE_H
#define FACE_H

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include <string>
#include <iostream>

using namespace std;

class Face : public Component{
public:
    Face(GameObject& associated);
    ~Face();
    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(string type);
private:
    int hitpoints;
	bool requestDelete, played;
	Sound* sound;
};

#endif