//
// Created by etien on 18/01/2023.
//

#ifndef OPENGLSANDBOX_PARTICLE_H
#define OPENGLSANDBOX_PARTICLE_H

#include <vector>
#include <glm/vec3.hpp>

class Particle {

public:
    Particle() = default;
    Particle(const glm::vec3 &position);

private:
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 acceleration;



};


#endif //OPENGLSANDBOX_PARTICLE_H
