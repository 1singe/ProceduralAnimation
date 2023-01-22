//
// Created by foura on 18/01/2023.
//

#define _USE_MATH_DEFINES

#include "utils.h"
#include "random.h"
#include <cmath>
#include <chrono>
#include <iostream>

namespace utils {

    using Random = effolkronium::random_static;

    glm::vec3 RandomPointInSphereRejection(const glm::vec3 &position, const float &radius){
        float x, y, z, d;
        do {
            x = Random::get(-radius, radius);
            y = Random::get(-radius, radius);
            z = Random::get(-radius, radius);
            d = x*x + y*y + z*z;
        } while (d>1);
        return position + glm::vec3{x, y, z};
    }



    glm::vec3 RandomPointInSphereDistributed(const glm::vec3 &position, const float &radius){
        float u = Random::get(0.f, radius);
        float x = Random::get<float>();
        float y = Random::get<float>();
        float z = Random::get<float>();

        float magnitude = sqrt(x*x + y*y + z*z);
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;

        float c = cbrt(u);

        return position + glm::vec3{x*c, y*x, z*c};

    }

    glm::vec3 RandomPointInSphereBetterDistributed(const glm::vec3 &position, const float &radius){
        float u = Random::get(0.f, 1.f);
        float v = Random::get(0.f, 1.f);
        float theta = u * M_2_PI;
        float phi = acos(2.f * v - 1.f);
        float r = cbrt(Random::get(0.f, 1.f));
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);
        return position + glm::vec3{r * sinPhi * cosTheta, r * sinPhi * sinTheta, r * cosPhi};
    }


    ScopedNanoTimer::ScopedNanoTimer(std::function<void(int)> callback) :
        t0(std::chrono::high_resolution_clock::now()),
        cb(std::move(callback)){}

    ScopedNanoTimer::~ScopedNanoTimer() {
        auto  t1 = std::chrono::high_resolution_clock::now();
        auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0).count();
        cb(nanos);
    }

    void PrintTime(int nanos){
        std::cout << nanos << std::endl;
    }

    Box::Box(const glm::vec3 &position, const glm::vec3 &dimensions) : position(position), dimensions(dimensions) {

    }
} // utils