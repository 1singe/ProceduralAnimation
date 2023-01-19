//
// Created by foura on 18/01/2023.
//

#ifndef OPENGLSANDBOX_EXPIRING_PARTICLE_H
#define OPENGLSANDBOX_EXPIRING_PARTICLE_H


#include "particle.h"

class ExpiringParticle : public Particle {
public:
    ExpiringParticle() = default;
    ExpiringParticle(const glm::vec3 &position, const float &mass, const float &drag, const float &lifetime);

    ExpiringParticle(const glm::vec3 &position, const float &mass, const float &drag, const float &lifetime,
                     const glm::vec3 &startUpVec, const float &startUpForce);

    void init() override;
    void update(const float &elapsedTime) override;
    void render3D(const RenderApi3D &api) override;
    float lifetime = 1;
    float timeSinceSpawn = 0;
};


#endif //OPENGLSANDBOX_EXPIRING_PARTICLE_H
