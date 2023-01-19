//
// Created by foura on 18/01/2023.
//

#ifndef OPENGLSANDBOX_PARTICLE_SYSTEM_H
#define OPENGLSANDBOX_PARTICLE_SYSTEM_H


#include "particle.h"
#include "expiring_particle.h"

class ParticleSystem : public Entity {

private:
    float innerTimer = 0;
    std::vector<ExpiringParticle> particles = std::vector<ExpiringParticle>();

public:
    float startUpForce = 0;
    float spawnRadius = 1;
    bool active = true;
    bool canCollideWithGround= true;
    float lifetime = 1;
    float spawnRate = 4;
    float mass = 1;
    float drag = 0.07;
    bool gravityEnabled = true;


    ParticleSystem() = default;
    explicit ParticleSystem(const glm::vec3 &position);
    ParticleSystem(const glm::vec3 &position, const float &spawnRadius, const float &lifetime, const float &spawnRate,
                   const float &mass, const float &drag);

    void init() override;
    void update(const float &elapsedTime) override;
    void render3D(const RenderApi3D &api) override;


};


#endif //OPENGLSANDBOX_PARTICLE_SYSTEM_H
