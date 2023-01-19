//
// Created by foura on 18/01/2023.
//

#include "particle_system.h"
#include <random>
#include <iostream>
#include "utils.h"
#include "expiring_particle.h"
#include "glm/geometric.hpp"
#include "drawbuffer.h"
#include "glm/ext/matrix_transform.hpp"


void ParticleSystem::init() {

}

void ParticleSystem::update(const float &elapsedTime) {
    innerTimer += elapsedTime;
    if(active && (innerTimer >= 1 / spawnRate)) {
        innerTimer = 0;
        glm::vec3 spawnPoint = utils::RandomPointInSphereRejection(position, spawnRadius);
        ExpiringParticle particle = ExpiringParticle(spawnPoint, mass, drag, lifetime, glm::normalize(spawnPoint - position), startUpForce);
        particles.emplace_back(particle);

    }
    for(auto it = particles.begin(); it != particles.end();){
        it->update(elapsedTime);
        it->timeSinceSpawn += elapsedTime;
        if(gravityEnabled){
            it->AddForce(utils::GRAVITY * it->mass);
        }
        if(canCollideWithGround && (it->position.y <= 0)){
            it->position.y = 0;
        }
        if(it->timeSinceSpawn >= it->lifetime){
            it = particles.erase(it);
        } else {
            ++it;
        }

    }





}

void ParticleSystem::render3D(const RenderApi3D &api) {
    auto vertices = std::vector<glm::vec3>();
    auto colors = std::vector<glm::vec4>();

    for(auto& particle : particles){
        vertices.push_back(particle.position);
        colors.emplace_back(1, 1, 1, 1);
    }

    Buffer3D buffer3D;

    CreateBuffer3DParams createCubeBufferParams;
    createCubeBufferParams.pVertices = vertices.data();
    createCubeBufferParams.pNormals = nullptr;
    createCubeBufferParams.pColors = colors.data();
    createCubeBufferParams.vertexCount = vertices.size();
    createBuffer3D(buffer3D, createCubeBufferParams);

    auto modelMat = glm::translate(glm::identity<glm::mat4>(), position);
    api.buffer(buffer3D, eDrawMode::Points, nullptr);

    deleteBuffer3D(buffer3D);

    /*
    for(auto& particle : particles){
        particle.render3D(api);
    }
     */
}

ParticleSystem::ParticleSystem(const glm::vec3 &position) : Entity(position) {}


ParticleSystem::ParticleSystem(const glm::vec3 &position,
                               const float &spawnRadius,
                               const float &lifetime, const float &spawnRate, const float &mass, const float &drag) :
       Entity(position),
       innerTimer(0),
       particles(std::vector<ExpiringParticle>()),
       spawnRadius(spawnRadius),
       active(true),
       lifetime(lifetime),
       spawnRate(spawnRate),
       mass(mass),
       drag(drag),
       gravityEnabled(true) {}
