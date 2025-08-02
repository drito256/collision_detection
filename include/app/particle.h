#ifndef PARTICLE_H
#define PARTICLE_H

#include "shader.h"

class Particle{
public:
    Particle(glm::mat4 model_matrix, glm::vec3 initial_velocity,
             glm::vec3 initial_rotation, float angle);
    ~Particle() = default;
    
    glm::mat4 get_model();

    void scale(const float &factor);
    void translate(const glm::vec3 &new_pos);

    glm::vec4 get_translation(const glm::mat4 &mat);
    glm::quat get_rotation(const glm::mat4 &mat);
    float get_scale(const glm::mat4 &mat);

    void update(const float &dt);
    void render();

    bool check_collision(const Particle &p);

private:
    glm::mat4 model_matrix;
    float angle;
    glm::vec3 initial_velocity;
    glm::vec3 initial_rotation;
};

#endif
