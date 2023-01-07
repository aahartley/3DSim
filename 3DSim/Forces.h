#pragma once
#include "Constants.h"
#include "Vector3f.h"
#include "Particle.h"
#include "Random.h"

struct Forces {

	static Vector3f gravity(const Particle& p) {
		return Vector3f(0, -GRAVITY * p.mass, 0);
	}
	static Vector3f airResistance(Particle& p, float d) {
		return p.vel * -d;
	}
	static Vector3f wind(Particle& p,float x, float y, float z, float d) {
		return (Vector3f(x, y, z) * d);
	}
	static Vector3f gravPoint(Particle& p, float aMass, Vector3f aPos, float pow) {
		Vector3f dist = p.pos - aPos;

		return (dist.unitVector() * ((aMass * p.mass) / std::pow(dist.magnitude(), pow)) * -G);
	}
	static Vector3f gravLine(Particle& p, Vector3f start, Vector3f dir, float L, float aMass, float pow) {
		Vector3f dist = p.pos - start;
		float lengthP = dist.dot(dir);
		Vector3f rai = start - dir * lengthP;
		if (lengthP > L)rai = p.pos - (start + dir * L);
		else if (lengthP <= 0 || lengthP >= L)rai = rai;
		else if (lengthP < 0)rai = dist;
		return (rai.unitVector() * ((aMass * p.mass) / std::pow(dist.magnitude(), pow)) * -G);

	}
	static Vector3f randForce(Particle& p, Random& random, float dt, float scale) {
		return random.randUVSphere() * (scale / dt);
	}
	static void limitVelMin(Particle& p, float speed) {
		Vector3f smallest = p.oldVel.unitVector() * speed;
		if (smallest.magnitude() >= p.oldVel.magnitude())smallest = p.oldVel;
		if (p.vel.magnitude() < smallest.magnitude())p.vel = smallest;

	}
	static Vector3f potentialField(Particle& p, float aMass, Vector3f cPos, float pow, float radius) {
		Vector3f dist = p.pos - cPos;

		return (dist.unitVector() * ((aMass * p.mass) / std::pow(radius-dist.magnitude(), pow)) * G);
	}
	static Vector3f steering(Particle& p, Vector3f cPos,float radius) {
		Vector3f dist = cPos - p.pos ;
		float sClose = dist.dot(p.vel.unitVector());
		float tc = 0.5f;
		float dc = p.vel.magnitude() * tc;
		if (sClose > dc) {
			Vector3f xClose = p.pos + p.vel.unitVector() * sClose;
			float dis = (xClose - cPos).magnitude();
			if (dis < radius) {
				Vector3f vPerp = xClose - cPos;
				Vector3f xT = cPos + vPerp.unitVector() * radius;
				float distT = (xT - p.pos).magnitude();
				float vT = p.vel.dot((xT - p.pos) / distT);
				float tt = distT / vT;
				float deltaVs = (p.vel.unitVector().cross((xT - p.pos))).magnitude() / tt;
				float as = 2 * deltaVs / tt;
				float e = vPerp.unitVector().dot(p.sumForces);
				if (as - e >= 0) {
					return vPerp.unitVector() * as;
				}
				else return Vector3f(0, 0, 0);
			}
			else return Vector3f(0, 0, 0);
		}
		else return Vector3f(0, 0, 0);

	}
};