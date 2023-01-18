//
// Created by foura on 18/01/2023.
//

#ifndef OPENGLSANDBOX_BURST_H
#define OPENGLSANDBOX_BURST_H


#include "particle.h"

class Burst : Entity {

private:
    float lifetime;
    int particleAmount;
    std::vector<Particle> particles;
public:
    Burst() = default;
    Burst(const float &lifetime, const int &particleAmount);
    void init() override;
    void update(const float &elapsedTime) override;



};


#endif //OPENGLSANDBOX_BURST_H
