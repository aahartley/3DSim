#pragma once
#include "Vector3f.h"

class Particle {
public:
	Vector3f acc;
	Vector3f vel;
	Vector3f pos;
	
	Vector3f oldAcc;
	Vector3f oldVel;
	Vector3f oldPos;

	float mass;
	float invM;
	float radius;
	float age;

	bool active;

	Vector3f sumForces;

	Particle();
	virtual ~Particle();

	void integrate(float dt);
	void addForce(Vector3f force);
	void clearForces();

	void testAndDeactivate();
};