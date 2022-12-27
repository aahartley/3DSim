#include "ParticleGenerator.h"

void ParticleGenerator::generateParticles(ParticleList& pL, float time, float timestep) {
	if (time >= start && time <= end) {
		n = rate * timestep;
		f = f + ((rate * timestep) - n);
		if (f > 1) {
			n++;
			f--;
		}
		for (int i = 0; i < n; i++) {
			Particle p;
			p.pos.x = (float)(std::rand() %100+1);
			p.pos.y = (float)(std::rand() % 100 + 1);
			p.vel.z = 30;
			pL.add(p);
		}
	}
}