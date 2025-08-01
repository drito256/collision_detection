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
    void rotate(glm::vec3 axis, float degree);

    void update();
    void render();

private:
    glm::mat4 model_matrix;
    glm::vec3 initial_velocity;
};

#endif
