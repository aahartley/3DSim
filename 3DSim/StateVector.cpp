#include "StateVector.h"

StateVector::StateVector(ParticleList& pL) {
	state = new Vector3f[MAX_PARTICLES*2];
	for (int i = 0; i < MAX_PARTICLES; i++) {
			state[i] = pL.particles[i].pos;
			state[i+MAX_PARTICLES] = pL.particles[i].vel;

		
	}
}
void StateVector::updatePL(ParticleList& pL, float dt) {
	for (int i = 0; i < MAX_PARTICLES; i++) {
		pL.particles[i].pos = state[i];
		pL.particles[i].vel = state[i + MAX_PARTICLES];
		pL.particles[i].age += dt;

		
	}
}
void StateVector::update(ParticleList& pL) {
	for (int i = 0; i < MAX_PARTICLES; i++) {
		state[i]=pL.particles[i].pos  ;
		state[i + MAX_PARTICLES]=pL.particles[i].vel ;


	}
}

Vector3f StateVector::environmentForces(ParticleList& pL, StateVector& sOld, int i, float time) {
	Vector3f sumForces;
		//sumForces += Forces::gravity(pL.particles[i]);
		if (sOld.state[i+MAX_PARTICLES].magnitude() >= 0.0) {
			
			sumForces += Forces::airResistance(pL.particles[i], 0.4f); //air resitance -dV
			sumForces += Forces::wind(pL.particles[i], -12.5, 0, 0, 0.4f); //wind Vwind-v
		}
	
	return sumForces;
}

Vector3f StateVector::particleForces(ParticleList& pL, StateVector& sOld, int i, int j, float time) {
	Vector3f dist = pL.particles[j].pos - pL.particles[i].pos;
	
	return (dist.unitVector() * ((pL.particles[i].mass * pL.particles[j].mass) / std::pow(dist.magnitude(), 2)) * G);
}
StateVector StateVector::integrate(StateVector& sOld, float dt) {
	StateVector sNew;
	sNew = sOld + *this * dt;
	return sNew;
}
StateVector StateVector::getDerivatives(ParticleList& pL,float time) {
	StateVector sDeriv;
	Vector3f forceJI;

	for (int i = 0; i < MAX_PARTICLES; i++) {
		sDeriv.state[i+MAX_PARTICLES] = environmentForces(pL, *this, i, time) * pL.particles[i].invM;
	}
	//#pragma omp parallel for num_threads(12)
	for (int i = 0; i < MAX_PARTICLES - 1; i++) {
		if (pL.particles[i].active) {
			for (int j = i + 1; j < MAX_PARTICLES; j++) {
				if (pL.particles[j].active) {
					forceJI = particleForces(pL, *this, i, j, time);
					sDeriv.state[i + MAX_PARTICLES] = sDeriv.state[i + MAX_PARTICLES] + (forceJI * pL.particles[i].invM);
					sDeriv.state[j + MAX_PARTICLES] = sDeriv.state[j + MAX_PARTICLES] - (forceJI * pL.particles[j].invM);
				}
			}
		}
	}
	return sDeriv;
}
StateVector StateVector::dynamics(ParticleList& pL, float time) {
	StateVector sDeriv = getDerivatives(pL, time);
	for (int i = 0; i < MAX_PARTICLES; i++) {
		sDeriv.state[i] = this->state[i+MAX_PARTICLES];
		pL.particles[i].oldVel = this->state[i + MAX_PARTICLES];
		pL.particles[i].oldPos = this->state[i];

	}
	return sDeriv;
}
float StateVector::dot(const StateVector& sv) const {
	float result = 0;
	for (int i = 0; i < MAX_PARTICLES; i++) {
		result += state[i].dot(sv.state[i]);
		result += state[i + MAX_PARTICLES].dot(sv.state[i + MAX_PARTICLES]);
	}
	return result;
}

StateVector StateVector::operator + (const StateVector& sv) const {
	StateVector result;
	for (int i = 0; i < MAX_PARTICLES; i++) {
		result.state[i] = state[i] + sv.state[i];
		result.state[i + MAX_PARTICLES] = state[i + MAX_PARTICLES] + sv.state[i + MAX_PARTICLES];
	}
	return result;
}
StateVector StateVector::operator - (const StateVector& sv) const {
	StateVector result;
	for (int i = 0; i < MAX_PARTICLES; i++) {
		result.state[i] = state[i] - sv.state[i];
		result.state[i + MAX_PARTICLES] = state[i + MAX_PARTICLES] - sv.state[i + MAX_PARTICLES];
	}
	return result;
}
StateVector StateVector::operator * (const float n) const {
	StateVector result;
	for (int i = 0; i < MAX_PARTICLES; i++) {
		result.state[i] = state[i]*n;
		result.state[i + MAX_PARTICLES] = state[i+MAX_PARTICLES]*n;
	}
	return result;
}