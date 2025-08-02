#ifndef PARTICLE_H
#define PARTICLE_H

#include "shader.h"
#include "constants.h"
#include "plane.h"

class Particle{
public:
    Particle(glm::mat4 model_matrix, glm::vec3 initial_velocity,
             glm::vec3 initial_rotation, float angle);
    ~Particle() = default;
    
    glm::mat4 get_model() const ;

    void scale(const float &factor);
    void translate(const glm::vec3 &new_pos);

    glm::vec4 get_translation(const glm::mat4 &mat) const ;
    glm::quat get_rotation(const glm::mat4 &mat) const ;
    float get_scale(const glm::mat4 &mat) const ;

    void update(const float &dt);
    void render();

    bool check_collision(const Particle &p) const;
    bool check_collision(const Plane &p) const;

private:
    glm::mat4 model_matrix;
    float angle;
    glm::vec3 initial_velocity;
    glm::vec3 initial_rotation;
};

#endif
