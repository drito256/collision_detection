#ifndef PARTICLE_H
#define PARTICLE_H

#include "shader.h"
#include "constants.h"
#include "plane.h"

#include <random>

class Particle{
public:
    Particle(glm::mat4 model_matrix, glm::vec3 initial_velocity,
             glm::vec3 initial_rotation, float angle);
    ~Particle() = default;
    
    glm::mat4 get_model() const ;

    void scale(const float &factor);
    void translate(const glm::vec3 &new_pos);

    glm::vec4 get_translation() const ;
    glm::quat get_rotation() const ;
    float get_scale() const ;

    void update(const float &dt);
    void render();

    glm::vec3 get_color();
    void set_color(glm::vec3 color);

private:
    glm::mat4 model_matrix;
    float angle;
    glm::vec3 initial_velocity;
    glm::vec3 initial_rotation;
    glm::vec3 color;
};

#endif
