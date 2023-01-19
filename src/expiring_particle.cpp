//
// Created by foura on 18/01/2023.
//

#include "expiring_particle.h"
#include "utils.h"

ExpiringParticle::ExpiringParticle(const glm::vec3 &position, const float& mass, const float &drag, const float &lifetime):
    Particle(position, mass, drag),
    lifetime(lifetime),
    timeSinceSpawn(0)
    {}

ExpiringParticle::ExpiringParticle(const glm::vec3 &position, const float& mass, const float &drag, const float &lifetime, const glm::vec3 &startUpVec, const float &startUpForce):
        Particle(position, mass, drag, startUpVec, startUpForce),
        lifetime(lifetime),
        timeSinceSpawn(0)
{}

void ExpiringParticle::init() {
    Particle::init();
}

void ExpiringParticle::update(const float &elapsedTime) {
    Particle::update(elapsedTime);
}

void ExpiringParticle::render3D(const RenderApi3D &api) {
    float shade = 1- (timeSinceSpawn / lifetime);
    api.solidSphere(position, 0.01, 16, 16, {1, shade, shade, 1});
}


