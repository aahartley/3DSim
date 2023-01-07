#pragma once
#include "Constants.h"
#include "Particle.h"
#include "Polygon.h"

struct ParticleCollision {
    Particle* p;
    float dn = 0;
    float dn1 = 0;
    Vector3f normal;

    ParticleCollision() { p = nullptr; };
    ParticleCollision(Particle& p) :p(&p) {};
    bool ParticleDetection(Polygon& poly);
    void ParticleDetermination(float deltaTime);
    void ParticleResponse(Polygon& poly);
};


