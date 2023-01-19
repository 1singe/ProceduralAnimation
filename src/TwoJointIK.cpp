//
// Created by etien on 19/01/2023.
//

#include "TwoJointIK.h"

Bone::Bone(const glm::vec3 &position) : position(position) {}

void Bone::render3D(const RenderApi3D &api, glm::vec3 parent_pos, glm::quat parent_rot) const {

    glm::vec3 worldPos = parent_pos + parent_rot * position;
    glm::quat worldRot = parent_rot * rotation;

    glm::vec3 child_pos = children.empty() ? glm::vec3{0.5, 0, 0} : children.front().position;

    api.bone(child_pos, {0.6f, 0.8f, 1.f, 1.f}, worldRot, worldPos);

    for(const auto& child : children) {
        child.render3D(api, worldPos, worldRot);
    }

    printf("%f %f %f\n", worldPos.x, worldPos.y, worldPos.z);
}

TwoJointIK::TwoJointIK() : hip(position) {
    hip.children.emplace_back(glm::vec3{0, -0.7, 0});
    knee = &hip.children.back();
    knee->children.emplace_back(glm::vec3{0, -1.5, 0});
    heel = &knee->children.back();
}

void TwoJointIK::init() {

}

void TwoJointIK::update(const float &deltaTime) {

}

void TwoJointIK::render3D(const RenderApi3D &api) {
    hip.render3D(api, position);
}




