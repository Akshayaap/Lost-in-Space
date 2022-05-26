#include <cmath>
#include "util.h"
#include "Vec2.h"



Vec2::Vec2() {
	this->x = 0;
	this->y = 0;
	this->r = 0;
	this->t = 0;
}

Vec2::Vec2(double x, double y) {
	this->x = x;
	this->y = y;
	AdjustRT();
}


Vec2::Vec2(const Vec2& v) {
    this->x = v.x;
    this->y = v.y;
    this->AdjustRT();
}

Vec2& Vec2::operator = (const Vec2& v) {
    this->x = v.x;
    this->y = v.y;
    this->AdjustRT();
    return *this;
}

Vec2::Vec2(double r, double t, bool f) {
    this->r = r;
    this->t = t;
    this->AdjustXY();
}

Vec2::~Vec2() {}

void Vec2::AdjustXY() {
	this->x = this->r * cos(this->t);
	this->y = this->r * sin(this->t);
}

void Vec2::AdjustRT() {
    this->r = sqrt(this->x * this->x + this->y * this->y);
    if (this->x >= 0) {
        if (this->y >= 0) {
            this->t = asin(this->y / this->r);
        }
        else {
            this->t = 2 * PI + asin(this->y / this->r);
        }
    }
    else {
        if (this->y >= 0) {
            this->t = PI + acos(this->x / this->r);
        }
        else {
            this->t = PI + asin(this->y / this->r);
        }
    }
}



Vec2 Vec2::operator + (const Vec2& v) const {
    return Vec2(this->x + v.x, this->y + v.y);
}
Vec2 Vec2::operator + (const double r)const {
    return Vec2(this->r + r, this->t, true);
}

Vec2 Vec2::operator - (const Vec2& v)const {
    return Vec2(this->x - v.x, this->y - v.y);
}

Vec2& Vec2::operator +=(const Vec2& v) {
    this->x += v.x;
    this->y += v.y;
    AdjustRT();
    return *this;
}

Vec2& Vec2::operator += (const double r) {
    this->r += r;
    this->AdjustXY();
    return *this;
}


Vec2& Vec2::operator -= (const Vec2& v) {
    this->x -= v.x;
    this->y -= v.y;
    this->AdjustRT();
    return *this;
}

Vec2 Vec2::operator* (double s)const {
    return Vec2(this->x * s, this->y * s);
}

Vec2& Vec2::operator *=(double s) {
    this->r *= s;
    AdjustXY();
    return *this;
}

Vec2& Vec2::Norm() {
    this->r = 1;
    this->AdjustXY();
    return *this;
}

Vec2 Vec2::GetNorm() const {
    return Vec2(this->x / this->r, this->y / this->r);
}

Vec2& Vec2::Ortho() {
    double temp = this->x;
    this->x = this->y;
    this->x = -temp;
    this->AdjustRT();
    return *this;
}

Vec2 Vec2::GetOrtho()const {
    return Vec2(this->y, -this->x);
}

double Vec2::Dot(const Vec2& v){
    return this->x* v.x + this->y * v.y;
}

double Vec2::Cross(const Vec2& v) {
    return this->x * v.y - this->y * v.x;
}
