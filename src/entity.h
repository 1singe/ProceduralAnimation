//
// Created by foura on 18/01/2023.
//

#ifndef OPENGLSANDBOX_ENTITY_HPP
#define OPENGLSANDBOX_ENTITY_HPP

#include <glm/vec3.hpp>


#include "renderapi.h"
#include <vector>

class Entity {
public:
    virtual void init() = 0;
    virtual void update(const float& elapsedTime) = 0;
    virtual void render3D(const RenderApi3D& api) = 0;

    explicit Entity(const glm::vec3 &position);

protected:
    glm::vec3 position;
};

#endif //OPENGLSANDBOX_ENTITY_HPP
