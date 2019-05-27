#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Component.h"
#include "Rect.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#if defined (_WIN64) || defined (_WIN32)
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

using namespace std;
class Component ;
class GameObject {
public:
	GameObject();
	~GameObject();
	void Update(float dt);
	void Render();
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	void RemoveComponent(string type);
	Component* GetComponent(string type);
	Rect box;
	void Start();
	bool started;
	double angleDeg;
	void NotifyCollision(GameObject& other);
private:
	vector<shared_ptr<Component>> components;
	bool isDead;
};

#endif