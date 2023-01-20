//
// Created by etien on 20/01/2023.
//

#include "Spider.h"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/gtx/euler_angles.hpp"

Spider::Spider() {

}

void Spider::init() {

    int idx = 0;
    for(int side = -1; side <= 1; side += 2) {
        for(int i = 0; i < 4; i++) {

            glm::vec3& target = leg_targets[idx];
            TwoJointIK& ik = legs[idx++];
            glm::quat q = glm::angleAxis(glm::radians(-37.5f + 25.f * i), glm::vec3{0, 1, 0});
            q *= glm::angleAxis(glm::radians(90.f), glm::vec3{-1, 0, 0});

            glm::vec3 legDir = q * glm::vec3{side, 0, 0};

            ik = TwoJointIK(position, legDir * 0.1f, {side*0.3f, 0, 0}, {side*0.5f, 0, 0});
            ik.hip.rotation = q;

            target = position + (legDir * 0.6f) + glm::vec3{0, -0.1, 0};
            ik.targetHeelPosition = target;
        }
    }

}

void Spider::update(const float &deltaTime) {

    static float time = 0.0f;
    time += 0.05;
    for(int i = 0; i < legs.size(); i++) {

        TwoJointIK& ik = legs[i];
        const glm::vec3& center = leg_targets[i];

        float offset = i&1 ? 0 : glm::pi<float>();

        glm::quat q = glm::angleAxis(time - offset, glm::vec3(1.f, 0.f, 0.f));
        glm::vec3 finalTarget = q * glm::vec3{0, 0, 0.2} + center;
        finalTarget.y = glm::clamp(finalTarget.y, 0.f, FLT_MAX);

        ik.targetHeelPosition = finalTarget;
    }

    for(auto& leg : legs) {
        leg.position = position;
        leg.update(deltaTime);
    }



}

void Spider::render3D(const RenderApi3D &api) {

    api.solidSphere(position, 0.1, 10, 10, {0, 0.4, 1.0, 1.0});
    api.solidSphere(position + glm::vec3{0, 0, -0.2}, 0.15, 10, 10, {0, 0.4, 1.0, 1.0});

    for(auto& leg : legs) {
        leg.render3D(api);
    }

}
