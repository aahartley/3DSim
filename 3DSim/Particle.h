#pragma once
#include "Vector3f.h"

class Particle {
public:
	Vector3f acc;
	Vector3f vel;
	Vector3f pos;

	float mass;
	float invM;
	Vector3f sumForces;

	Particle();
	virtual ~Particle();

	void integrate(float dt);
	void addForce(Vector3f force);
	void clearForces();

};