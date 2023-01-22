//
// Created by foura on 18/01/2023.
//

#ifndef OPENGLSANDBOX_UTILS_H
#define OPENGLSANDBOX_UTILS_H

#include <chrono>
#include <functional>
#include <utility>
#include "glm/vec3.hpp"

namespace utils {

    constexpr glm::vec3 GRAVITY = {0, -9.81, 0};

    glm::vec3 RandomPointInSphereRejection(const glm::vec3 &position, const float &radius);
    glm::vec3 RandomPointInSphereDistributed(const glm::vec3 &position, const float &radius);
    glm::vec3 RandomPointInSphereBetterDistributed(const glm::vec3 &position, const float &radius);
    void PrintTime(int nanos);

    struct ScopedNanoTimer
    {
        std::chrono::high_resolution_clock::time_point t0;
        std::function<void(int)> cb;

        explicit ScopedNanoTimer(std::function<void(int)> callback);

        ~ScopedNanoTimer();
    };

    struct Box
    {
    public:
        glm::vec3 position;
        glm::vec3 dimensions;

        Box(const glm::vec3 &position, const glm::vec3 &dimensions);
    };

} // utils

#endif //OPENGLSANDBOX_UTILS_H
