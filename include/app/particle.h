#ifndef PARTICLE_H
#define PARTICLE_H

#include "shader.h"
#include "constants.h"
#include "plane.h"

#include <random>

class Particle{
public:
    Particle(glm::mat4 model_matrix,
             glm::vec3 initial_rotation, float rot_angle,
             float rev_angle, float rev_radius, float angular_velocity);
    ~Particle() = default;
    
    glm::mat4 get_model() const ;

    void scale(const float &factor);
    void translate(const glm::vec3 &new_pos);

    glm::vec4 get_translation() const ;
    glm::quat get_rotation() const ;
    float get_scale() const ;

    void update(const float &dt);

    glm::vec3 get_color();
    void set_color(glm::vec3 color);
    
    void set_colliding(bool value);
    bool is_colliding();

private:
    glm::mat4 model_matrix;
    glm::vec3 initial_rotation; // rotation axis
    float rot_angle; // rotation angle
    float rev_angle; // revolution angle 
    float rev_radius;
    float angular_velocity;
    glm::vec3 color;
    bool colliding;
};

#endif
