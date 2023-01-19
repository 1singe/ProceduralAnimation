//
// Created by foura on 18/01/2023.
//

#include "particle_system.h"
#include <random>
#include <iostream>
#include "utils.h"
#include "expiring_particle.h"


void ParticleSystem::init() {

}

void ParticleSystem::update(const float &elapsedTime) {
    innerTimer += elapsedTime;
    if(active && (innerTimer >= 1 / spawnRate)) {
        innerTimer = 0;
        particles.emplace_back(utils::RandomPointInSphereRejection(position, spawnRadius), mass, drag, lifetime);
    }
    for(auto it = particles.begin(); it != particles.end();){
        it->update(elapsedTime);
        it->timeSinceSpawn += elapsedTime;
        if(gravityEnabled){
            it->AddForce(utils::GRAVITY * it->mass);
        }
        if(it->timeSinceSpawn >= it->lifetime){
            it = particles.erase(it);
        } else {
            ++it;
        }

    }





}

void ParticleSystem::render3D(const RenderApi3D &api) {
    for(auto& particle : particles){
        particle.render3D(api);
    }
}

ParticleSystem::ParticleSystem(const glm::vec3 &position) : Entity(position) {}


ParticleSystem::ParticleSystem(const glm::vec3 &position,
                               const float &spawnRadius,
                               const float &lifetime, const float &spawnRate, const float &mass, const float &drag) :
       Entity(position),
       innerTimer(0),
       particles(std::vector<ExpiringParticle>()),
       spawnRadius(spawnRadius),
       active(true),
       lifetime(lifetime),
       spawnRate(spawnRate),
       mass(mass),
       drag(drag),
       gravityEnabled(true) {}
