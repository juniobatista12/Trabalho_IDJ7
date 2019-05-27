#ifndef VEC2D_H
#define VEC2D_H

#define PI 3.1415
#include <cmath>
#include <iostream>

using namespace std;

class Vec2d{
public:
    Vec2d();
    Vec2d(float x, float y);
    float x, y;
    Vec2d operator*(float d);
    float GetMagnitude();
    Vec2d GetNormalizado();
    Vec2d operator-(Vec2d b);
    float GetInclinacao();
    Vec2d GetRotacao(float angulo);
    Vec2d operator+(Vec2d b);
	void operator+=(Vec2d b);
	void operator*=(float d);
	Vec2d operator/(float d);
	bool operator>(Vec2d v);
	bool operator<(Vec2d v);
	friend ostream& operator<< (ostream&, Vec2d);
};
#endif