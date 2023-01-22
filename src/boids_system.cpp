//
// Created by foura on 19/01/2023.
//

#include "boids_system.h"
#include "utils.h"
#include "glm/geometric.hpp"
#include "drawbuffer.h"
#include "glm/ext/matrix_transform.hpp"

void BoidSystem::update(const float &elapsedTime) {
    updateNumberOfBoids(targetAmount);
    for(auto &boid : boids){
        int neighborCount = 0;
        boid.separationVector = {};
        boid.velocityVector = {};
        boid.centerOfMass = {};
        for(auto &neighbor : boids){
            if(&boid == &neighbor) continue;
            float distance = glm::distance(boid.position, neighbor.position);
            if(distance < awarenessRadius){
                neighborCount++;
                boid.velocityVector += neighbor.speed;
                boid.centerOfMass += neighbor.position;
                if(distance < protectedRadius) {
                    boid.separationVector += boid.position - neighbor.position;
                }
            }
        }
        if(neighborCount != 0){
            boid.velocityVector /= neighborCount;
            boid.centerOfMass /= neighborCount;
        }
        boid.targetVector = target - boid.position;
        boid.speed += (boid.separationVector * separationWeight);
        boid.speed += (boid.velocityVector - boid.speed) * alignmentWeight;
        boid.speed += (boid.centerOfMass - boid.position) * cohesionWeight;
        boid.speed += glm::normalize(boid.targetVector) * targetWeight;

        if(constrained) {
            if(boid.position.x <= box.position.x - box.dimensions.x/2){
                boid.speed.x += avoidance;
            }
            if(boid.position.x >= box.position.x + box.dimensions.x/2){
                boid.speed.x -= avoidance;
            }
            if(boid.position.y <= box.position.y - box.dimensions.y/2){
                boid.speed.y += avoidance;
            }
            if(boid.position.y >= box.position.y + box.dimensions.y/2){
                boid.speed.y -= avoidance;
            }
            if(boid.position.z <= box.position.z - box.dimensions.z/2){
                boid.speed.z += avoidance;
            }
            if(boid.position.z >= box.position.z + box.dimensions.z/2){
                boid.speed.x -= avoidance;
            }
        }

        float mag = boid.speed.length();
        if(mag <= minSpeed*elapsedTime){
            boid.speed = (boid.speed/mag)*minSpeed*elapsedTime;
        } if (mag >= maxSpeed*elapsedTime){
            boid.speed = (boid.speed/mag)*maxSpeed*elapsedTime;
        }

        boid.update(elapsedTime * simulation);

    }



    /*
    updateNumberOfBoids(targetAmount);
    for(auto it = boids.begin(); it != boids.end(); ++it) {
        glm::vec3 velocityVector = {};
        glm::vec3 centerOfMassVector = {};
        glm::vec3 separationVector = {};
        bool inside = true;
        int neighborCount = 0;
        for(auto it_neigh = boids.begin(); it_neigh != boids.end(); ++it_neigh) {
            if(it == it_neigh) continue;
            float distance = glm::distance(it->position, it_neigh->position);
            if(distance > awarenessRadius) continue;
            neighborCount++;
            //Alignement
            velocityVector += it_neigh->speed;
            //Cohesion
            centerOfMassVector += it_neigh->position;
            if(distance > protectedRadius) continue;
            //Separation
            separationVector += it->position - it_neigh->position;
        }
        if(neighborCount){
            centerOfMassVector /= neighborCount;
            velocityVector /= neighborCount;
            it->speed = ((velocityVector * alignmentWeight) + (centerOfMassVector * cohesionWeight) + (separationVector * separationWeight));
        }
        if(constrained) {
            glm::vec3 next_position = it->position + it->speed * simulation * elapsedTime;
            glm::vec3 d = next_position - box.position;
            inside = abs(dot(d, {1, 0, 0})) <= box.dimensions.x * 0.5f &&
                     abs(dot(d, {0, 1, 0})) <= box.dimensions.y * 0.5f &&
                     abs(dot(d, {0, 0, 1})) <= box.dimensions.z * 0.5f;
            it->speed *= inside ? 1: -1;
        }
        it->update(elapsedTime * simulation);
    }
     */
}


/*if(constrained) {
glm::vec3 d = it->position - box.position;
glm::vec3 upper_bounds = box.position + box.dimensions * 0.5f;
glm::vec3 lower_bounds = box.position - box.dimensions * 0.5f;
glm::vec3 next_position = it->position + it->speed * elapsedTime * simulation;

if(next_position.x <= lower_bounds.x || next_position.x >= upper_bounds.x){
it->speed *= -1;
}
if(next_position.y <= lower_bounds.y || next_position.y >= upper_bounds.y){
it->speed *= -1;
}
if(next_position.z <= lower_bounds.z || next_position.z >= upper_bounds.z){
it->speed *= -1;
}
}
 */
/*if(constrained) {
            glm::vec3 d = it->position - box.position;
            if(it->position.x <= box.position.x - box.dimensions.x/2){
                it->AddForce({avoidance, 0, 0});
            }
            if(it->position.x >= box.position.x + box.dimensions.x/2){
                it->AddForce({-avoidance, 0, 0});
            }
            if(it->position.y <= box.position.y - box.dimensions.y/2){
                it->AddForce({0, +avoidance,0});
            }
            if(it->position.y >= box.position.y + box.dimensions.y/2){
                it->AddForce({0, -avoidance,0});
            }
            if(it->position.z <= box.position.z - box.dimensions.z/2){
                it->AddForce({0,0,+avoidance});
            }
            if(it->position.z >= box.position.z + box.dimensions.z/2){
                it->AddForce({0,0,-avoidance});
            }
        }*/

//it->AddForce((velocityVector * alignmentWeight) + (centerOfMassVector * cohesionWeight) + (separationVector * separationWeight));

BoidSystem::BoidSystem(const int &amount) : Entity({}), targetAmount(amount) {}

void BoidSystem::updateNumberOfBoids(const int &desiredAmount) {
    if (desiredAmount == boidsAmount) {
        return;
    } else if (desiredAmount < boidsAmount) {
        deleteBoids(desiredAmount);
    } else {
        spawnBoids(desiredAmount);
    }
    boidsAmount = desiredAmount;
}

void BoidSystem::spawnBoids(const int &desiredAmount) {
    for(; boidsAmount < desiredAmount; boidsAmount++){
        boids.emplace_back(utils::RandomPointInSphereRejection(position, spawnRadius));
    }
}

void BoidSystem::deleteBoids(const int &desiredAmount) {
    for(;boidsAmount > desiredAmount; boidsAmount--){
        boids.pop_back();
    }
}

void BoidSystem::render3D(const RenderApi3D &api) {
    auto vertices = std::vector<glm::vec3>();
    auto colors = std::vector<glm::vec4>();

    for(auto& boid : boids){
        vertices.push_back(boid.position);
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

}

void BoidSystem::init() {

}

