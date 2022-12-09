#include "Particle.h"

Particle::Particle() {
	this->mass = 1.0f;
	this->invM = 1.0f / this->mass;
	this->sumForces = Vector3f(0.0f, 0.0f, 0.0f);
	this->acc = Vector3f(0.0f, 0.0f, 0.0f);
	this->vel = Vector3f(0.0f, 0.0f, 0.0f);
	this->pos = Vector3f(0.0f, 0.0f, 0.0f);

}

Particle::~Particle() {}

void Particle::addForce(Vector3f force) {
	sumForces += force;
}
void Particle::clearForces() {
	sumForces = Vector3f(0.0f, 0.0f, 0.0f);
}
void Particle::integrate(float dt) {
	acc = sumForces * invM;
	vel += acc * dt;
	pos += vel * dt;
	clearForces();

}