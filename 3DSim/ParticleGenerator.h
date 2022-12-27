#pragma once
#include "ParticleList.h"
#include <random>
class ParticleGenerator {
public:
	ParticleGenerator(int rate, float start, float end) :rate(rate), start(start),end(end) {}
	void generateParticles(ParticleList& pL, float time, float timestep);
	int rate = 0;
	float n = 0;
	float f = 0;
	float start = 0;
	float end = 0;
};