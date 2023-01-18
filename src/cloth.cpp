//
// Created by etien on 18/01/2023.
//

#include "cloth.h"
#include "drawbuffer.h"

#include "glm/geometric.hpp"
#include "glm/gtx/norm.hpp"


Constraint::Constraint(ClothParticle* p1, ClothParticle* p2) : p1(p1), p2(p2) {
    glm::vec3 vec = p1->position - p2->position;
    rest_distance = glm::length(vec);
}

void Constraint::satisfyConstraint() const {
    glm::vec3 p1_to_p2 = p2->position - p1->position; // vector from p1 to p2
    float current_distance = glm::length(p1_to_p2); // current distance between p1 and p2
    glm::vec3 correctionVector = p1_to_p2 * (1.f - rest_distance/current_distance); // The offset vector that could moves p1 into a distance of rest_distance to p2
    glm::vec3 correctionVectorHalf = correctionVector * 0.5f; // Lets make it half that length, so that we can move BOTH p1 and p2.
    p1->offsetPos(correctionVectorHalf);
    p2->offsetPos(-correctionVectorHalf);
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
, height(2)
, width(2)
{
    createParticles();
}

Cloth::Cloth(const glm::vec3& position, float width, float height, int num_particles_width, int num_particles_height)
: Entity(position)
, num_particles_height(num_particles_height)
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

            glm::vec3 pos = glm::vec3(width * (x/(float)num_particles_width), height * (y/(float)num_particles_height), 0);
            pos += this->position;
            particles[y*num_particles_width+x] = ClothParticle(pos);

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

ClothParticle* Cloth::getParticle(int x, int y) {
    return &particles[y*num_particles_width + x];
}

void Cloth::makeConstraint(int x1, int y1, int x2, int y2) {
    constraints.emplace_back(getParticle(x1, y1), getParticle(x2, y2));
}

void Cloth::addForce(const glm::vec3 &direction) {
    for(auto& particle : particles) {
        particle.addForce(direction);
    }

}

void Cloth::update(const float &elapsedTime) {
    addForce(glm::vec3(0, -0.005, 0)); // add gravity each frame, pointing down

    for(int i=0; i < iteration_count; i++) {// iterate over all constraints several times
        for(auto& constraint : constraints) {
            constraint.satisfyConstraint(); // satisfy constraint.
        }
    }

    for(auto& p : particles) {
        p.update(elapsedTime);
    }

    floorCollision(0.f);
}

void Cloth::ballCollision(const glm::vec3& center, float radius) {

    float radius_offset = radius + 0.003f;
    for(auto& particle : particles) {

        glm::vec3 v = particle.position - center;
        float l = glm::length(v);
        if (l < radius_offset) {  // if the particle is inside the ball
            particle.offsetPos(glm::normalize(v) * (radius_offset-l)); // project the particle to the surface of the ball
        }

    }

}


void Cloth::floorCollision(float height) {
    const float adjusted_height = height+0.01f;
    for(auto& particle : particles) {
        if (particle.position.y < adjusted_height) {
            particle.position.y = adjusted_height;
        }
    }
}

void Cloth::render3D(const RenderApi3D &api) {

    auto vertices = std::vector<glm::vec3>();
    auto colors = std::vector<glm::vec4>();

    vertices.resize(num_particles_width * num_particles_height * 6);

    for(int x=0; x<num_particles_width-1; x++) {
        for (int y = 0; y < num_particles_height - 1; y++) {

//            vertices.push_back(getParticle(x, y)->position);
//            vertices.push_back(getParticle(x, y+1)->position);
//            vertices.push_back(getParticle(x+1, y)->position);
//
//            vertices.push_back(getParticle(x+1, y+1)->position);
//            vertices.push_back(getParticle(x+1, y)->position);
//            vertices.push_back(getParticle(x, y+1)->position);

            vertices.push_back(getParticle(x, y)->position);
            vertices.push_back(getParticle(x, y+1)->position);
            vertices.push_back(getParticle(x+1, y)->position);
            vertices.push_back(getParticle(x, y)->position);

            vertices.push_back(getParticle(x+1, y+1)->position);
            vertices.push_back(getParticle(x+1, y)->position);
            vertices.push_back(getParticle(x, y+1)->position);
            vertices.push_back(getParticle(x+1, y+1)->position);

        }
    }

    colors.resize(vertices.size());
    for (unsigned int i = 0; i < vertices.size(); ++i) {
        colors[i] = {0.8, 0.5, 0.2, 1.0};
    }


    Buffer3D buffer3D;

    CreateBuffer3DParams createCubeBufferParams;
    createCubeBufferParams.pVertices = vertices.data();
    createCubeBufferParams.pNormals = nullptr;
    createCubeBufferParams.pColors = colors.data();
    createCubeBufferParams.vertexCount = vertices.size();
    createBuffer3D(buffer3D, createCubeBufferParams);

    auto modelMat = glm::translate(glm::identity<glm::mat4>(), position);
    api.buffer(buffer3D, eDrawMode::Lines, nullptr);

    deleteBuffer3D(buffer3D);

}

void ClothParticle::addForce(glm::vec3 f) {
    acceleration += f/mass;
}

void ClothParticle::update(double elapsedTime) {
    if(movable) {
        glm::vec3 temp = position;
        position = position + (position - old_position) * (1-drag) + (acceleration*(float)0.016);
        old_position = temp;
        acceleration = glm::vec3(0,0,0); // acceleration is reset since it HAS been translated into a change in position (and implicitely into velocity)
    }
}

void ClothParticle::offsetPos(glm::vec3 offset) {
    if(movable)
        position += offset;
}

ClothParticle::ClothParticle(const glm::vec3 &pos)
        : position(pos)
        , old_position(pos)
        , acceleration(glm::vec3(0,0,0))
        , mass(1)
        , movable(true) {}
