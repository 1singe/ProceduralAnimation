//
// Created by foura on 19/01/2023.
//

#ifndef OPENGLSANDBOX_BOIDS_SYSTEM_H
#define OPENGLSANDBOX_BOIDS_SYSTEM_H


#include "entity.h"
#include "boid.h"
#include "utils.h"

class BoidSystem : public Entity {

public:

    utils::Box box = {{0,0,0},{4, 4, 4}};
    float avoidance = 1;
    float awarenessRadius = 10;
    float protectedRadius = 0.1f;
    int targetAmount = 10;
    float awarenessAngle = 1;
    float simulation = 1;
    float spawnRadius = 1;
    int boidsAmount = 0;
    float cohesionWeight = 0.3f;
    float alignmentWeight = 0.3f;
    float separationWeight = 1;
    bool constrained = true;
    float minSpeed = 1;
    float maxSpeed = 2;
    glm::vec3 target = {};
    float targetWeight = 0.2f;
    std::vector<Boid> boids = {};

    BoidSystem() = default;
    explicit BoidSystem(const int &amount);

    void init() override;
    void update(const float &elapsedTime) override;
    void render3D(const RenderApi3D &api) override;

    void spawnBoids(const int &desiredAmount);
    void deleteBoids(const int &amount);

    void updateNumberOfBoids(const int &desiredAmount);
};


#endif //OPENGLSANDBOX_BOIDS_SYSTEM_H
