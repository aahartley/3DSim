#include "Particle.h"

Particle::Particle() {
	this->mass = 1.0f;
	this->invM = 1.0f / this->mass;
	this->sumForces = Vector3f(0.0f, 0.0f, 0.0f);
	this->acc = Vector3f(0.0f, 0.0f, 0.0f);
	this->vel = Vector3f(0.0f, 0.0f, 0.0f);
	this->pos = Vector3f(0.0f, 0.0f, 0.0f);
	this->oldAcc = acc;
	this->oldVel = vel;
	this->oldPos = pos;
	this->active = false;
	this->radius = 0.3f;
	this->age = 0.0f;

}

Particle::~Particle() {}

void Particle::addForce(Vector3f force) {
	sumForces += force;
}
void Particle::clearForces() {
	sumForces = Vector3f(0.0f, 0.0f, 0.0f);
}
Vector3f Particle::vOPTranslate(Vector3f vel, Vector3f translate, float dt) {
	return vel + translate/dt;
}
Vector3f Particle::vOPScale(Vector3f vel, float scale) {
	return vel *scale;
}
Vector3f Particle::vOPRotate(Vector3f vel, float angle, Vector3f dir) {
	Vector3f rotation = vel * std::cosf(angle) + (dir.cross(vel)) * std::sinf(angle) + dir * (1 - std::cosf(angle))*(dir.dot(vel));
	return rotation + vel;
}
float Particle::vOPVortex(Vector3f vel, Vector3f cPos, Vector3f dir, float L, float R, float t) {
	Vector3f dist = pos - cPos;
	float length = dir.dot(dist);
	float angVel = 0;
	if (length >= 0 && length <= L) {
		Vector3f ri = dist - dir * length;
		if (ri.magnitude() > R) {
			float fr = 3.0f;
			float freq = std::pow((R / ri.magnitude()), t) * fr;
			float fmax = 5.0f;
			if (freq < fmax)
				angVel = 2 * PI * freq;
			else angVel = 2 * PI * fmax;
		}
	}
	return angVel;
}
void Particle::integrate(float dt) {
	age += dt;
	oldAcc = acc;
	oldVel = vel;
	oldPos = pos;
	acc = sumForces * invM;
	vel += acc * dt;
	//if (std::fmodf(age, 0.016f) == 0) {
	//	//pos += vOPTranslate((vel+oldVel)*0.5f,Vector3f(0,4,0),dt) * dt;
	//	//pos += vOPRotate((vel + oldVel) * 0.5f, PI / 4, Vector3f(0, 0, 1)) * dt;
	//}
	//else
	//pos += (vel + oldVel) * 0.5f * dt;
	pos += vel * dt;

	clearForces();

}

void Particle::testAndDeactivate() {
	if (age > 10)active = false;
}