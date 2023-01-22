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
    explicit Particle(const glm::vec3 &position);
    Particle(const glm::vec3 &position, const float &mass, const float &drag);
    Particle(const glm::vec3 &position, const float &mass, const float &drag, const glm::vec3 &startUpVec, const float &startupForce);

    glm::vec3 speed = {};
    glm::vec3 acceleration = {};
    float mass = 1.0f;
    float drag = 0.005f;
    bool movable = true;

    void init() override;
    void update(const float &deltaTime) override;
    void render3D(const RenderApi3D& api) override;
    void addForce(const glm::vec3 &force);
    void offsetPos(const glm::vec3 &offset);

private:
    glm::vec3 forces = {};

};


#endif //OPENGLSANDBOX_PARTICLE_H
