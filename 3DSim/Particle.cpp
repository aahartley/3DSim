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
	this->active = true;
	this->radius = 1.0f;
	this->age = 0.0f;

}

Particle::~Particle() {}

void Particle::addForce(Vector3f force) {
	sumForces += force;
}
void Particle::clearForces() {
	sumForces = Vector3f(0.0f, 0.0f, 0.0f);
}
void Particle::integrate(float dt) {
	age += dt;
	oldAcc = acc;
	oldVel = vel;
	oldPos = pos;
	acc = sumForces * invM;
	vel += acc * dt;
	pos += vel * dt;
	clearForces();

}

void Particle::testAndDeactivate() {
	if (age > 10)active = false;
}