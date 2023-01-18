//
// Created by foura on 18/01/2023.
//

#include "particle_system.h"
#include <random>


void ParticleSystem::init() {

}

void ParticleSystem::update(const float &elapsedTime) {
    innerTimer += elapsedTime;
    if(!active || innerTimer <= 1.f / spawnRate) {
        return;
    }
    innerTimer = 0;
    particles.emplace_back(new Particle(position, mass, drag));
}

ParticleSystem::ParticleSystem() {




}
