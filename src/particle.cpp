//
// Created by etien on 18/01/2023.
//

#include "particle.h"
#include "glm/ext/matrix_transform.hpp"


Particle::Particle(const glm::vec3 &position, const float& mass, const float &drag):
        Entity(position),
        drag(drag),
        mass(mass),
        speed(0),
        acceleration(0),
        forces(0)
{}

void Particle::init() {

}

void Particle::update(const float &elapsedTime) {
    //Update physics
    acceleration = forces / mass;
    speed += acceleration * elapsedTime;
    position += speed * elapsedTime;
    speed *= (1-drag);
    forces = glm::vec3();
}

void Particle::render3D(const RenderApi3D &api) {


    auto translate = glm::translate(glm::identity<glm::mat4>(), position);
    glm::vec4 color = {1, 1, 1, 1};
    api.solidCube(1, color, &translate);
}


void Particle::AddForce(const glm::vec3 &force) {
    forces += force;
}


