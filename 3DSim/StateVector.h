#pragma once
#include "Vector3f.h"
#include "ParticleList.h"
class StateVector {
public:
	Vector3f* state;
	int lastI = 0;
	int lastJ = 0;

	StateVector() { state = new Vector3f[MAX_PARTICLES * 2]; };
	StateVector(ParticleList& pL);
	~StateVector() {};
	void updatePL(ParticleList& pL, float dt);
	void update(ParticleList& pL);
	StateVector integrate(StateVector& sOld, float dt);
	StateVector getDerivatives(ParticleList& pL, float dt);
	StateVector dynamics(ParticleList& pL, float dt);
	Vector3f environmentForces(ParticleList& pL, StateVector& sOld, int i, float dt);

	float dot(const StateVector& v) const;     

	StateVector operator + (const StateVector& sv) const;
	StateVector operator - (const StateVector& sv) const;  
	StateVector operator * (const float n) const; 

};