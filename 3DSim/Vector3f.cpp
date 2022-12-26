#include "Vector3f.h"
#include <math.h>

Vector3f::Vector3f() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3f::Vector3f(float x, float y, float z) :x(x), y(y), z(z) {}

Vector3f::~Vector3f() {}

//fix
//Vector3f Vector3f::rotate(const float angle) const {
//	Vector3f result;
//	result.x = x * cos(angle) - y * sin(angle);
//	result.y = x * sin(angle) + y * cos(angle);
//	return result;
//}

float Vector3f::magnitude() const {
	return sqrtf(x * x + y * y + z*z);
}

float Vector3f::magnitudeSquared() const {
	return (x * x + y * y + z*z);
}

Vector3f& Vector3f::normalize() {
	float length = magnitude();
	if (length != 0.0) {
		x /= length;
		y /= length;
		z /= length;
	}
	return *this;
}

Vector3f Vector3f::unitVector() const {
	Vector3f result = Vector3f(0.0f, 0.0f, 0.0f);
	float length = magnitude();
	if (length != 0.0) {
		result.x = x / length;
		result.y = y / length;
		result.z = z / length;
	}
	return result;
}


Vector3f Vector3f::normal() const {
	return Vector3f(-y,x,0).normalize();
}


float Vector3f::dot(const Vector3f& v) const {
	return (x * v.x) + (y * v.y) + (z*v.z);
}

Vector3f Vector3f::cross(const Vector3f& v) const {
	return Vector3f((y*v.z-z*v.y),-(x*v.z-z*v.x),(x*v.y-y*v.x));
}

Vector3f& Vector3f::operator = (const Vector3f& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

bool Vector3f::operator == (const Vector3f& v) const {
	return x == v.x && y == v.y && z== v.z;
}

bool Vector3f::operator != (const Vector3f& v) const {
	return !(*this == v);
}

Vector3f Vector3f::operator + (const Vector3f& v) const {
	Vector3f result;
	result.x = x + v.x;
	result.y = y + v.y;
	result.z = z + v.z;
	return result;
}

Vector3f Vector3f::operator - (const Vector3f& v) const {
	Vector3f result;
	result.x = x - v.x;
	result.y = y - v.y;
	result.z = z - v.z;
	return result;
}

Vector3f Vector3f::operator * (const float n) const {
	Vector3f result;
	result.x = x * n;
	result.y = y * n;
	result.z = z * n;
	return result;
}

Vector3f Vector3f::operator / (const float n) const {
	Vector3f result;
	result.x = x / n;
	result.y = y / n;
	result.z = z / n;
	return result;
}

Vector3f& Vector3f::operator += (const Vector3f& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3f& Vector3f::operator -= (const Vector3f& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3f& Vector3f::operator *= (const float n) {
	x *= n;
	y *= n;
	z *= n;
	return *this;
}

Vector3f& Vector3f::operator /= (const float n) {
	x /= n;
	y /= n;
	z /= n;
	return *this;
}

Vector3f Vector3f::operator - () {
	Vector3f result;
	result.x = x * -1;
	result.y = y * -1;
	result.z = z * -1;
	return result;
}
