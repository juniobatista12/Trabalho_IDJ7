#ifndef RECT_H
#define RECT_H

#include "Vec2d.h"

class Rect {
private:
    /* data */
public:
    Rect();
    Rect(int x, int y, int w, int h);
    ~Rect();
    float x, y, h, w;
    bool Contains(int x, int y);
    bool Contains(Vec2d b);
	void SetCentro(float x, float y);
	void SetCentro(Vec2d v);
	Vec2d GetVec();
	Vec2d GetVecCentralizado();
};


#endif