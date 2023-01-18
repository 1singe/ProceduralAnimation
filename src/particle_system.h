//
// Created by foura on 18/01/2023.
//

#ifndef OPENGLSANDBOX_PARTICLE_SYSTEM_H
#define OPENGLSANDBOX_PARTICLE_SYSTEM_H


#include "particle.h"

class ParticleSystem : Entity {

private:
    float innerTimer = 0;
    std::vector<Particle*> particles;

public:
    float spawnRadius = 1;
    bool active = true;
    float lifetime = 1;
    float spawnRate = 4;
    float mass = 1;
    float drag = 0.035;

    ParticleSystem();
    void init() override;
    void update(const float &elapsedTime) override;


};


#endif //OPENGLSANDBOX_PARTICLE_SYSTEM_H
