//
// Created by foura on 18/01/2023.
//

#ifndef OPENGLSANDBOX_EXPIRING_PARTICLE_H
#define OPENGLSANDBOX_EXPIRING_PARTICLE_H


#include "particle.h"

class ExpiringParticle : Particle {
private:
    float lifetime;
    float timeSinceSpawn;
public:
    ExpiringParticle() = default;
    ExpiringParticle(const glm::vec3 &position, const float &mass, const float &drag, const float &lifetime);
    void init() override;
    void update(const float &elapsedTime) override;
};


#endif //OPENGLSANDBOX_EXPIRING_PARTICLE_H
