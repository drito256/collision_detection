#ifndef PARTICLE_SYS_H
#define PARTICLE_SYS_H

#include "particle.h"

#include <vector>
#include <array>

struct Vertex{
    glm::vec3 pos;
    // atr atr
};

class ParticleSystem{
public:
    ParticleSystem(glm::vec3 position, int count);
    ~ParticleSystem();

    void update();
    void render(Shader s);

private:
    glm::vec3 position;
    int count;

    std::vector<Particle> particles;
    std::array<Vertex, 36> vertices; // fixed gpu params for cube

    unsigned int vao;
    unsigned int vbo;

};



#endif
