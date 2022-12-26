#pragma once
#include <cmath>
#include <iostream>
class Vector3f {
public:
	float x, y, z;

	Vector3f();
	Vector3f(float x, float y, float z);
	virtual ~Vector3f();

	std::ostream& operator<<(std::ostream& out) {
		return out << x << ' ' << y << ' ' << z;
	}

    //Vector3f rotate(const float angle) const;    // v1.rotate(angle)

    float magnitude() const;                 // v1.magnitude()
    float magnitudeSquared() const;          // v1.magnitudeSquared()

    Vector3f& normalize();                       // v1.normalize()
    Vector3f unitVector() const;                 // v1.unitVector()
    Vector3f normal() const;                     // n = v1.normal()

    float dot(const Vector3f& v) const;          // v1.Dot(v2)
    Vector3f cross(const Vector3f& v) const;        // v1.Cross(v2)

    Vector3f& operator = (const Vector3f& v);        // v1 = v2
    bool operator == (const Vector3f& v) const;  // v1 == v2
    bool operator != (const Vector3f& v) const;  // v1 != v2

    Vector3f operator + (const Vector3f& v) const;   // v1 + v2
    Vector3f operator - (const Vector3f& v) const;   // v1 - v2
    Vector3f operator * (const float n) const;   // v1 * n
    Vector3f operator / (const float n) const;   // v1 / n
    Vector3f operator - ();                      // -v1

    Vector3f& operator += (const Vector3f& v);       // v1 += v2
    Vector3f& operator -= (const Vector3f& v);       // v1 -= v2
    Vector3f& operator *= (const float n);       // v1 *= n
    Vector3f& operator /= (const float n);       // v1 /= n
  
};


inline std::ostream& operator<<(std::ostream& out, const Vector3f& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}
//inline static Vec3 random() {
//	return Vec3(randomFloat(), randomFloat(), randomFloat());
//}
//
//inline static Vec3 random(float min, float max) {
//	return Vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
//}










