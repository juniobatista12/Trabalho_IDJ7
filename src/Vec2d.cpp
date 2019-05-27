#include "Vec2d.h"

Vec2d::Vec2d() : x(0), y(0) {}

Vec2d::Vec2d(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2d Vec2d::operator*(float d){
    return Vec2d(x*d, y*d);
}

float Vec2d::GetMagnitude(){
    return sqrt(x*x+y*y);
}

Vec2d Vec2d::GetNormalizado(){
    return Vec2d(x/GetMagnitude(), y/GetMagnitude());
}

Vec2d Vec2d::operator-(Vec2d b){
    return Vec2d(x-b.x, y-b.y);
}

float Vec2d::GetInclinacao(){
    return atan2(y, x);
}

Vec2d Vec2d::GetRotacao(float angulo){
    return Vec2d(x*cos(angulo)-y*sin(angulo), y*cos(angulo)+x*sin(angulo));
}

Vec2d Vec2d::operator+(Vec2d b){
    return Vec2d(x+b.x, y+b.y);
}

void Vec2d::operator+=(Vec2d b) {
	x += b.x;
	y += b.y;
}

void Vec2d::operator*=(float d) {
	x *= d;
	y *= d;
}

Vec2d Vec2d::operator/(float d) {
	return Vec2d(x / d, y / d);
}

bool Vec2d::operator>(Vec2d v) {
	return this->x > v.x && this->y > v.y;
}

bool Vec2d::operator<(Vec2d v) {
	return this->x < v.x && this->y < v.y;
}

ostream& operator<<(ostream& os, Vec2d v) {
	return os << "X: " << v.x << ", Y: " << v.y << endl;
}