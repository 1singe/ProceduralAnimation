//
// Created by foura on 19/01/2023.
//

#ifndef OPENGLSANDBOX_BOID_H
#define OPENGLSANDBOX_BOID_H


#include "particle.h"

class Boid : public Particle {
public:
    Boid();
    glm::vec3 velocityVector = {};
    glm::vec3 centerOfMass = {};
    glm::vec3 separationVector = {};
    glm::vec3 targetVector = {};
    explicit Boid(const glm::vec3 &position);
    void init() override;
    void update(const float& elapsedTime) override;
    void render3D(const RenderApi3D& api) override;
};


#endif //OPENGLSANDBOX_BOID_H
