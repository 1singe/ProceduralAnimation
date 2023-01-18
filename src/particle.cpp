//
// Created by etien on 18/01/2023.
//

#include "particle.h"

Particle::Particle(const glm::vec3 &position, const float& mass) :
        Entity(position),
        mass(mass){}

void Particle::init() {

}

void Particle::update(const float &elapsedTime) {

}

void Particle::render3D(const RenderApi3D &api) {

}


