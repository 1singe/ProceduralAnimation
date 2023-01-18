//
// Created by etien on 18/01/2023.
//

#ifndef OPENGLSANDBOX_PARTICLE_H
#define OPENGLSANDBOX_PARTICLE_H

#include <vector>
#include <glm/vec3.hpp>
#include "entity.h"

class Particle : public Entity {

public:
    Particle() = default;
    Particle(const glm::vec3 &position, const float &mass, const float &drag);

    glm::vec3 speed;
    glm::vec3 acceleration;
    float mass;
    float drag;

    void init() override;
    void update(const float &elapsedTime) override;
    void render3D(const RenderApi3D& api) override;
    void AddForce(const glm::vec3 &force);

private:
    glm::vec3 forces;

};


#endif //OPENGLSANDBOX_PARTICLE_H
