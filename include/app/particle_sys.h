#ifndef PARTICLE_SYS_H
#define PARTICLE_SYS_H

#include "particle.h"

#include <vector>
#include <array>

#include "vertex.h"

class ParticleSystem{
public:
    ParticleSystem(glm::vec3 position, int count);
//    ~ParticleSystem();

    std::vector<Particle>& get_particles();

    void update(float dt);
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
