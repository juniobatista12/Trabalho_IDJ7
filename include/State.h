#ifndef STATE_H
#define STATE_H

#include "GameObject.h"
#include <memory>
#include <vector>

using namespace std;

class State {
public:
	State();
	virtual ~State();
	virtual void LoadAssets() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Start();
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual weak_ptr<GameObject> AddObject(GameObject* object);
	virtual weak_ptr<GameObject> GetObjectPtr(GameObject* object);
	bool PopRequested();
	bool QuitRequested();
protected:
	void StartArray();
	virtual void UpdateArray(float dt);
	virtual void RenderArray();
	bool popRequested;
	bool quitRequested;
	bool started;
	vector<shared_ptr<GameObject>> objectArray;
};

#endif