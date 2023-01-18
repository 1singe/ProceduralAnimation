//
// Created by etien on 18/01/2023.
//

#ifndef OPENGLSANDBOX_CLOTH_H
#define OPENGLSANDBOX_CLOTH_H

#include <vector>
#include <memory>

#include "entity.h"
#include "particle.h"


struct Constraint {

    Constraint(Particle* p1, Particle* p2);

    float rest_distance;
    Particle* p1;
    Particle* p2;

    void satisfyConstraint() const;

};



class Cloth : public Entity {

public:
    Cloth();
    Cloth(const glm::vec3& position);
    Cloth(const glm::vec3& position, float width, float height, int num_particles_width, int num_particles_height);

    int iteration_count = 10;

    Particle* getParticle(int x, int y);
    void addForce(const glm::vec3& direction);

    // Entity override
    void init() override {}
    void update(const float& elapsedTime) override;
    void render3D(const RenderApi3D& api) override;

    void ballCollision(const glm::vec3 &center, float radius);
    void floorCollision(float height);

private:

    std::vector<Particle> particles;
    std::vector<Constraint> constraints;

    int num_particles_width;
    int num_particles_height;
    float width;
    float height;

    void createParticles();

    void makeConstraint(int x1, int y1, int x2, int y2);


};


#endif //OPENGLSANDBOX_CLOTH_H
