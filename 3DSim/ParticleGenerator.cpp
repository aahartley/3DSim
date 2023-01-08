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
			float speed = rand.randGauss(mu, delta/3);
			float f = rand.randUniform(0, 1);
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
			//p.vel = randUVUniformW(Vector3f(0, -1, 0), delta / 3);
			//p.pos = randUniPos(Vector3f(-30, 100, 60), Vector3f(0, -1, 0), 10);//center, surface norm, radius,,, with offset

			//from triangle
			//bool inside = false;
			//std::vector<Vector3f> triVert;
			//triVert.push_back(Vector3f(-30.0f, 50.0f, 60.0f)); //p0
			//triVert.push_back(Vector3f(-30.0f, 60.0f, 65.0f)); //p1
			//triVert.push_back(Vector3f(-30.0f, 50.0f, 70.0f)); //p3
			//Triangle* triangle = new Triangle(triVert, Vector3f(0, 0, 0));
			//while (!inside) {
			//	float u = randUniform(0, 1);
			//	float v = randUniform(0, 1);
			//	if (u + v <= 1) { 
			//		inside = true;
			//		p.pos = triangle->vertices[0] * u + triangle->vertices[1] * v + triangle->vertices[2] * (1 - u - v);
			//		p.vel = randUVUniformW(triangle->surfaceNormalU, delta / 3)*speed;
			//	}


			//}

			//from sphere
			//Vector3f randU = rand.randUVSphere();
			//Vector3f center(0, 10, 0);
			//float radius = 5.0f;
			//float radiusF = std::cbrtf(f) * radius;
			////p.pos = center + randU * radius;//outside sphere
			//p.pos = center + randU * radiusF;
			//p.vel = rand.randUVUniformW(randU, delta / 3);

			//rand pos
			p.pos = Vector3f(rand.createRandUniform(-100, 100), rand.createRandUniform(0, 100), rand.createRandUniform(-100, 100));
			p.vel = Vector3f(1, 1, 1);
			//add offset here
			p.pos += p.vel * (f * timestep);
			p.mass = rand.randUniform(1,500);
			p.active = true;
			pL.add(p);
		}
	}
}