#ifndef TITLESTATE_H
#define TITLESTATE_H
#include "State.h"
#include "Timer.h"
class TitleState : public State {
public:
	TitleState();
	~TitleState();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void Start();
	void Pause();
	void Resume();
private:
	Timer timer;
	bool texten;
};

#endif