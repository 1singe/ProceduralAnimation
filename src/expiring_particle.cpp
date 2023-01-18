//
// Created by foura on 18/01/2023.
//

#include "expiring_particle.h"

ExpiringParticle::ExpiringParticle(const glm::vec3 &position, const float& mass, const float &drag, const float &lifetime):
        Particle(position, mass, drag),
        lifetime(lifetime),
        timeSinceSpawn(0)
{
}

void ExpiringParticle::init() {
    Particle::init();
}

void ExpiringParticle::update(const float &elapsedTime) {
    Particle::update(elapsedTime);
    timeSinceSpawn += elapsedTime;
    if(timeSinceSpawn >= lifetime){
        delete this;
    }
}
