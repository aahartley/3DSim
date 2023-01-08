#pragma once
#include "Vector3f.h"
#include "ParticleList.h"
class StateVector {
public:
	Vector3f* state;


	StateVector() { state = new Vector3f[MAX_PARTICLES * 2]; };
	StateVector(ParticleList& pL);
	~StateVector() {};
	void updatePL(ParticleList& pL, float dt);
	void update(ParticleList& pL);
	StateVector integrate(StateVector& sOld, float dt);
	StateVector getDerivatives(ParticleList& pL, float time);
	StateVector dynamics(ParticleList& pL, float time);
	Vector3f environmentForces(ParticleList& pL, StateVector& sOld, int i, float time);
	Vector3f particleForces(ParticleList& pL, StateVector& sOld, int i, int j, float time);


	float dot(const StateVector& v) const;     

	StateVector operator + (const StateVector& sv) const;
	StateVector operator - (const StateVector& sv) const;  
	StateVector operator * (const float n) const; 

};