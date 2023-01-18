//
// Created by etien on 18/01/2023.
//

#include "particle.h"

Particle::Particle(const glm::vec3 &position, const glm::vec3 &speed, const glm::vec3 &acceleration) :
    Entity(position),
    speed(speed),
    acceleration(acceleration)
{}

Particle::Particle(const glm::vec3 &position) : Entity(position),
    speed(glm::vec3()),
    acceleration(glm::vec3())
{}
