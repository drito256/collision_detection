#ifndef PARTICLE_H
#define PARTICLE_H

#include "shader.h"


class Particle{
public:
    Particle(glm::mat4 model_matrix, glm::vec3 initial_velocity);
    ~Particle() = default;
    
    glm::mat4 get_model();

    void scale(float factor);
    void translate(glm::vec3 new_pos);

    void update(float dt);
    void render();

private:
    glm::mat4 model_matrix;
    float ro, phi; // rotation angles
    glm::vec3 initial_velocity;
};

#endif
