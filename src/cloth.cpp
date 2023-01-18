//
// Created by etien on 18/01/2023.
//

#include "cloth.h"
#include "glm/geometric.hpp"
#include "glm/gtx/norm.hpp"


Constraint::Constraint(Particle* p1, Particle* p2) : p1(p1), p2(p2) {
    glm::vec3 vec = p1->position - p2->position;
    rest_distance = glm::length(vec);
}

void Constraint::satisfyConstraint() const {
    glm::vec3 p1_to_p2 = p2->position - p1->position; // vector from p1 to p2
    float current_distance = glm::length(p1_to_p2); // current distance between p1 and p2
    glm::vec3 correctionVector = p1_to_p2 * (1.f - rest_distance/current_distance); // The offset vector that could moves p1 into a distance of rest_distance to p2
    glm::vec3 correctionVectorHalf = correctionVector * 0.5f; // Lets make it half that length, so that we can move BOTH p1 and p2.
    p1->position += correctionVectorHalf;
    p2->position -= correctionVectorHalf;
}

Cloth::Cloth()
: num_particles_height(10)
, num_particles_width(10)
, height(1)
, width(1)
{
    createParticles();
}

Cloth::Cloth(const glm::vec3 &position)
: Entity(position)
, num_particles_height(10)
, num_particles_width(10)
, height(1)
, width(1)
{
    createParticles();
}

Cloth::Cloth(float width, float height, int num_particles_width, int num_particles_height)
: num_particles_height(num_particles_height)
, num_particles_width(num_particles_width)
, height(height)
, width(width)
{
    createParticles();
}

void Cloth::createParticles() {
    particles.clear();
    constraints.clear();

    particles.resize(num_particles_width * num_particles_height);

    // creating particles in a grid of particles from (0,0,0) to (width,-height,0)
    for(int x=0; x<num_particles_width; x++) {
        for(int y=0; y<num_particles_height; y++) {

            glm::vec3 pos = glm::vec3(width * (x/(float)num_particles_width), -height * (y/(float)num_particles_height), 0);
            particles[y*num_particles_width+x] = Particle(pos, 1.f, 0.005);

        }
    }

    // Connecting immediate neighbor particles with constraints (distance 1 and sqrt(2) in the grid)
    for(int x=0; x<num_particles_width; x++) {
        for(int y=0; y<num_particles_height; y++) {
            if (x<num_particles_width-1) makeConstraint(x,y,x+1,y);
            if (y<num_particles_height-1) makeConstraint(x,y,x,y+1);
            if (x<num_particles_width-1 && y<num_particles_height-1) makeConstraint(x,y,x+1,y+1);
            if (x<num_particles_width-1 && y<num_particles_height-1) makeConstraint(x+1,y, x,y+1);
        }
    }


    // Connecting secondary neighbors with constraints (distance 2 and sqrt(4) in the grid)
    for(int x=0; x<num_particles_width; x++) {
        for(int y=0; y<num_particles_height; y++) {
            if (x<num_particles_width-2) makeConstraint(x,y,x+2,y);
            if (y<num_particles_height-2) makeConstraint(x,y,x,y+2);
            if (x<num_particles_width-2 && y<num_particles_height-2) makeConstraint(x,y,x+2,y+2);
            if (x<num_particles_width-2 && y<num_particles_height-2) makeConstraint(x+2,y,x,y+2);
        }
    }

}

Particle* Cloth::getParticlePtr(int x, int y) {
    return &particles[y*num_particles_width + x];
}

void Cloth::makeConstraint(int x1, int y1, int x2, int y2) {
    constraints.emplace_back(getParticlePtr(x1, y1), getParticlePtr(x2, y2));
}

void Cloth::addForce(const glm::vec3 &direction) {
    for(auto& particle : particles) {
        // Add Force
        particle.acceleration += direction; // add the forces to each particle
    }

}

void Cloth::update(const float &elapsedTime) {
    for(int i=0; i < iteration_count; i++) {// iterate over all constraints several times
        for(auto& constraint : constraints) {
            constraint.satisfyConstraint(); // satisfy constraint.
        }
    }
}

void Cloth::ballCollision(const glm::vec3& center, float radius) {
    float radius_offset = std::pow(radius + 0.001f, 2.f);
    for(auto& particle : particles) {
        glm::vec3 v = particle.position - center + this->position;
        float l = glm::length2(v);
        if (l < radius_offset) {  // if the particle is inside the ball
            particle.position += (glm::normalize(v) * std::sqrt(radius_offset - l)); // project the particle to the surface of the ball
        }

    }

}


void Cloth::floorCollision(float height) {
    for(auto& particle : particles) {
        float v = particle.position.y - (height+0.01f);
        if (v < 0) {
            particle.position += glm::vec3{0, -v, 0};
        }
    }
}