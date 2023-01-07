#pragma once
#include "Particle.h"
#include "Forces.h"
#include <vector>
struct ParticleList {
	ParticleList() {
		particles = new Particle[MAX_PARTICLES];
		inactiveCount = MAX_PARTICLES;
		for (int i = MAX_PARTICLES-1; i >=0; i--) {
			inactiveStack.push_back(i);
		}

	}
	void add(Particle& p) {
		if (inactiveCount != 0) {

			particles[inactiveStack[inactiveCount-1]] = p;
			inactiveStack.pop_back();
			inactiveCount--;
		}

	}
	void clear() {
		for (int i = 0; i < MAX_PARTICLES;i++) {
			particles[i].active = false;
		}
	}
	void testAndDeactivate() {
		for (int i = 0; i < MAX_PARTICLES; i++) {
			if (particles[i].active) {
				particles[i].testAndDeactivate();
				if (!particles[i].active) {
					inactiveCount++;
					inactiveStack.push_back(i);
				}
			}
		}
	}
	void calcDeriv() {
		for (int i = 0; i < MAX_PARTICLES; i++) {
			if (particles[i].active) {
				particles[i].addForce(Forces::gravity(particles[i]));
				if (particles[i].vel.magnitude() >= 0.0) {

					particles[i].addForce(Forces::airResistance(particles[i], 0.4f)); //air resitance -dV
					particles[i].addForce(Forces::wind(particles[i], -12.5, 0, 0, 0.4f)); //wind Vwind-v
				   // pL.particles[i].addForce(Forces::potentialField(particles[i], 10.0f, Vector3f(-35, 0, 65), 2, 10.0f));
					//pL.particles[i].addForce(Forces::steering(particles[i], Vector3f(-35, 0, 65), 10.0f));
				   // pL.particles[i].addForce(Forces::gravPoint(particles[i],100.0f,Vector3f(0,10,0),2));
				   // pL.particles[i].addForce(Forces::gravLine(particles[i], Vector3f(0, 10, 0), Vector3f(0, 0, 1), 10.0f, 100.0f, 2));
					//pL.particles[i].addForce(Forces::randForce(particles[i], random, deltaTime, 5.0f));
					//Forces::limitVelMin(particles[i], 10.0f);
				}
			}
		}
	}
	Particle* particles;
	std::vector<int> inactiveStack;
	int inactiveCount;
};