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
			float speed = randGauss(mu, delta/3);
			float f = randUniform(0, 1);
			//general case
			//Vector3f dir (0, -1, 0);
			//dir = randUVGaussW(dir, delta / 3);
			//p.vel = dir * speed;
			
			//omnidirectional
		/*	p.pos = pos;
			p.vel = randUVSphere() * speed;*/

			//directed
	/*		Vector3f dir (0, -1, 0); 
			p.pos = pos;
			p.vel = randUVGaussW(dir, delta / 3) * speed;*/

			//from a disk
			p.vel = randUVUniformW(Vector3f(0, -1, 0), delta / 3);
			p.pos = randUniPos(Vector3f(-30, 100, 10), Vector3f(0, -1, 0), 10)+p.vel*(f*timestep);//center, surface norm, radius,,, with offset

			//from triangle

			//from sphere

			pL.add(p);
		}
	}
}