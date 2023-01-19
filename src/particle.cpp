//
// Created by etien on 18/01/2023.
//

#include "particle.h"
#include "glm/ext/matrix_transform.hpp"
#include "drawbuffer.h"


Particle::Particle(const glm::vec3 &position, const float& mass, const float &drag):
        Entity(position),
        drag(drag),
        mass(mass),
        speed(0),
        acceleration(0),
        forces(0),
        movable(true)
{}

Particle::Particle(const glm::vec3 &position, const float& mass, const float &drag, const glm::vec3 &startUpVec, const float &startUpForce):
        Entity(position),
        drag(drag),
        mass(mass),
        speed(0),
        acceleration(0),
        forces(0),
        movable(true)
{
    AddForce(startUpVec * startUpForce);
}

void Particle::init() {

}

void Particle::update(const float &elapsedTime) {
    //Update physics
    if(movable) {
        acceleration = forces / mass;
        speed += acceleration * elapsedTime;
        position += speed * elapsedTime;
        speed *= (1-drag);
        forces = glm::vec3();
    }
}

void Particle::render3D(const RenderApi3D &api) {
    api.solidSphere(position, 0.015f, 8, 8, {1, 1, 1, 1});
}


void Particle::AddForce(const glm::vec3 &force) {
    if(movable) forces += force;
}


void Particle::OffsetPos(const glm::vec3 &offset) {
    if(movable) position += offset;
}