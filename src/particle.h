//
// Created by etien on 18/01/2023.
//

#ifndef OPENGLSANDBOX_PARTICLE_H
#define OPENGLSANDBOX_PARTICLE_H

#include <vector>

class Particle {

public:
    Particle(const std::vector<float> &position);

private:
    std::vector<float> position;
    std::vector<float> acceleration;
    std::vector<float> speed;



};


#endif //OPENGLSANDBOX_PARTICLE_H
