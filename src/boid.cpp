//
// Created by foura on 19/01/2023.
//

#include "boid.h"

Boid::Boid(const glm::vec3 &position) : Particle(position)   {

}

Boid::Boid() : Particle() {

}

void Boid::update(const float &elapsedTime) {
    Particle::update(elapsedTime);
}

void Boid::init() {

}

void Boid::render3D(const RenderApi3D &api) {

}

