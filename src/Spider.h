//
// Created by etien on 20/01/2023.
//

#ifndef OPENGLSANDBOX_SPIDER_H
#define OPENGLSANDBOX_SPIDER_H


#include <array>
#include "entity.h"
#include "TwoJointIK.h"

class Spider : public Entity {

    std::array<TwoJointIK, 8> legs;
    std::array<glm::vec3, 8> leg_targets;


public:
    Spider();

    void init() override;
    void update(const float &deltaTime) override;
    void render3D(const RenderApi3D &api) override;
};


#endif //OPENGLSANDBOX_SPIDER_H
