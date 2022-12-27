#pragma once
#include "Particle.h"
#include <vector>
struct ParticleList {
	ParticleList(int num) {
		particles.reserve(num);
		inactiveStack.reserve(num);
		inactiveCount = 0;
		this->num = num;

	}
	void add(Particle& p) {
		if (inactiveCount != 0) {

			particles[inactiveStack[inactiveCount-1]] = p;
			inactiveStack.pop_back();
			inactiveCount--;
		}
		else if(particles.size() < num ) {
			particles.push_back(p);
		}
		//std::cout << particles.size() << '\n';
	}
	void clear() {
		for (Particle p : particles) {
			p.active = false;
		}
	}
	void testAndDeactivate() {
		for (int i = 0; i < particles.size(); i++) {
			if (particles[i].active) {
				particles[i].testAndDeactivate();
				if (!particles[i].active) {
					inactiveCount++;
					inactiveStack.push_back(i);
				}
			}
		}
	}
	std::vector<Particle> particles;
	std::vector<int> inactiveStack;
	int inactiveCount;
	int num;
};