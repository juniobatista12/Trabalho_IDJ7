#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "Component.h"
#include "GameObject.h"
#include <string>

using namespace std;

class CameraFollower : public Component {
public:
	CameraFollower(GameObject& go);
	void Update(float dt);
	void Render();
	bool Is(string type);
};

#endif // !CAMERAFOLLOWER_H


