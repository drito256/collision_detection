#ifndef PARTICLE_SYS_H
#define PARTICLE_SYS_H

#include "particle.h"

#include <vector>
#include <array>

#include "cube.h"

class ParticleSystem{
public:
    ParticleSystem(glm::vec3 position, int count); // particle == cube for now

    std::vector<Particle>& get_particles();

    void update(float dt);
    void render(Shader s);

private:
    glm::vec3 position;
    int count;

    std::vector<Particle> particles;
    Cube cube_mesh; // 1 per system
};



#endif
