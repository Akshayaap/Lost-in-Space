#pragma once
#define PI 3.141592653589793

inline double wrapAngle(double ang) {
	return fmod(ang, 2 * PI);
}
