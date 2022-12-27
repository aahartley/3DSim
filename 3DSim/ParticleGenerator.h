#pragma once
#include "Constants.h"
#include "ParticleList.h"
#include <random>
class ParticleGenerator {
public:
	ParticleGenerator(Vector3f pos,int rate, float start, float end) :pos(pos),rate(rate), start(start),end(end) {}
	void generateParticles(ParticleList& pL, float time, float timestep);
	int rate = 0;
	float n = 0;
	float f = 0;
	float start = 0;
	float end = 0;
	float mu = 10.0f; //mean speed
	float delta = 5.0f; //range of speed
	Vector3f pos;
	
};