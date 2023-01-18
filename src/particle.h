//
// Created by etien on 18/01/2023.
//

#ifndef OPENGLSANDBOX_PARTICLE_H
#define OPENGLSANDBOX_PARTICLE_H

#include <vector>
#include <glm/vec3.hpp>
#include "entity.h"

class Particle : public Entity{

public:
    Particle() = default;
    Particle(const glm::vec3 &position);
    Particle(const glm::vec3 &position, const glm::vec3 &speed, const glm::vec3 &acceleration);
    glm::vec3 speed;
    glm::vec3 acceleration;
private:




};


#endif //OPENGLSANDBOX_PARTICLE_H
