//
// Created by etien on 19/01/2023.
//

#ifndef OPENGLSANDBOX_TWOJOINTIK_H
#define OPENGLSANDBOX_TWOJOINTIK_H

#include <vector>
#include "entity.h"
#include "glm/detail/type_quat.hpp"
#include "glm/vec3.hpp"

struct Bone {
    glm::vec3 position = {};
    glm::quat rotation = glm::identity<glm::quat>();
    std::vector<Bone> children;

    explicit Bone() = default;
    explicit Bone(const glm::vec3 &position);

    void render3D(const RenderApi3D &api, glm::vec3 parent_pos = {}, glm::quat parent_rot = glm::identity<glm::quat>()) const;
};


struct TwoJointIK : public Entity {

    Bone hip, *knee, *heel;

    TwoJointIK();
    TwoJointIK(const glm::vec3& pos, const glm::vec3& hip_pos, const glm::vec3& knee_pos, const glm::vec3& heel_pos);

    glm::vec3 targetHeelPosition = {};

    void init() override;
    void update(const float &deltaTime) override;
    void render3D(const RenderApi3D &api) override;
};


#endif //OPENGLSANDBOX_TWOJOINTIK_H
