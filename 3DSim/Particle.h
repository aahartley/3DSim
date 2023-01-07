#pragma once
#include "Constants.h"
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

	Vector3f vOPTranslate(Vector3f vel, Vector3f translate, float dt);
	Vector3f vOPScale(Vector3f vel, float scale);
	Vector3f vOPRotate(Vector3f vel, float angle, Vector3f dir);
	float vOPVortex(Vector3f vel, Vector3f pos, Vector3f dir, float L, float R, float t);


	void testAndDeactivate();
};