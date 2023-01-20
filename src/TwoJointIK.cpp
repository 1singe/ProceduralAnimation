//
// Created by etien on 19/01/2023.
//

#include "glm/gtc/quaternion.hpp"

#include "TwoJointIK.h"

Bone::Bone(const glm::vec3 &position) : position(position) {}

void Bone::render3D(const RenderApi3D &api, glm::vec3 parent_pos, glm::quat parent_rot) const {

    glm::vec3 worldPos = parent_pos + parent_rot * position;
    glm::quat worldRot = parent_rot * rotation;

    glm::vec3 child_pos = children.empty() ? glm::vec3{0.5, 0, 0} : children.front().position;

//    api.solidSphere(worldPos, 0.1, 10, 10, {0.6f, 0.8f, 1.f, 1.f});
    api.bone(child_pos, {0.6f, 0.8f, 1.f, 1.f}, worldRot, worldPos);

    for(const auto& child : children) {
        child.render3D(api, worldPos, worldRot);
    }
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

    glm::quat a_gr = hip.rotation;
    glm::quat b_gr = hip.rotation * knee->rotation;

    glm::vec3 a = position + hip.position;
    glm::vec3 b = a + a_gr * knee->position;
    glm::vec3 c = b + b_gr * heel->position;
    glm::vec3 t = targetHeelPosition;

    glm::vec3 d = b_gr * glm::vec3(1, 0, 0);

    glm::quat& a_lr = hip.rotation;
    glm::quat& b_lr = knee->rotation;

    // Bend the knee to make the distance bewteen the hip and the knee
    // equals to the distance between the hip and the target
    float eps = 0.01;
    float lab = glm::length(b - a);
    float lcb = glm::length(b - c);
    float lat = glm::clamp(glm::length(t - a), eps, lab + lcb - eps);

    float ac_ab_0 = glm::acos(glm::clamp(glm::dot(
            glm::normalize(c - a),
            glm::normalize(b - a)), -1.f, 1.f));

    float ba_bc_0 = glm::acos(glm::clamp(glm::dot(
            glm::normalize(a - b),
            glm::normalize(c - b)), -1.f, 1.f));

    float ac_ab_1 = glm::acos(glm::clamp((lcb*lcb-lab*lab-lat*lat) / (-2*lab*lat), -1.f, 1.f));
    float ba_bc_1 = glm::acos(glm::clamp((lat*lat-lab*lab-lcb*lcb) / (-2*lab*lcb), -1.f, 1.f));

//    glm::vec3 axis0 = glm::normalize(glm::cross(c - a, b - a));
    glm::vec3 axis0 = glm::normalize(glm::cross(c - a, d));
    glm::quat r0 = glm::angleAxis(ac_ab_1 - ac_ab_0, glm::inverse(a_gr) * axis0);
    glm::quat r1 = glm::angleAxis(ba_bc_1 - ba_bc_0, glm::inverse(b_gr) * axis0);

    a_lr *= r0;
    b_lr *= r1;

    // Rotate the heel into place
    float ac_at_0 = glm::acos(glm::clamp(glm::dot(
            glm::normalize(c - a),
            glm::normalize(t - a)), -1.f, 1.f));

    glm::vec3 axis1 = glm::normalize(glm::cross(c - a, t - a));

    glm::quat r2 = glm::angleAxis(ac_at_0, glm::inverse(a_gr) * axis1);

    a_lr *= r2;

}

void TwoJointIK::render3D(const RenderApi3D &api) {
    hip.render3D(api, position);



    glm::vec3 a = position + hip.position;
    glm::vec3 b = a + hip.rotation * knee->position;
    glm::vec3 c = b + hip.rotation * knee->rotation * heel->position;
    glm::vec3 t = targetHeelPosition;

    api.solidSphere(a, 0.1, 10, 10, {1.0f, 0.0f, 0.0f, 1.f});
    api.solidSphere(b, 0.1, 10, 10, {0.0f, 1.0f, 0.0f, 1.f});
    api.solidSphere(c, 0.1, 10, 10, {0.0f, 0.0f, 1.0f, 1.f});

    api.solidSphere(t, 0.1, 10, 10, {1.f, 0.0f, 1.f, 1.f});

}




