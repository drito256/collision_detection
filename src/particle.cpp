#include "../include/app/particle.h"
#include <random>


Particle::Particle(glm::mat4 model_matrix, glm::vec3 initial_velocity,
                   glm::vec3 initial_rotation, float angle) :
                model_matrix{model_matrix},
                initial_velocity{initial_velocity},
                initial_rotation{initial_rotation},
                angle{angle}
                {};

void Particle::update(const float &dt){
    glm::vec4 translation = get_translation();
        
    
    translation =  translation + 
                  (glm::vec4(0.f, -Physics::gravity * (dt   * dt) / 20.f, 0.f, 0.f) + 
                   glm::vec4(initial_velocity * dt, 0.0));

    this->model_matrix = glm::rotate(this->model_matrix, 
                                     angle, 
                                     glm::normalize(initial_rotation));
    this->model_matrix[3] = translation;
}

glm::mat4 Particle::get_model() const {
    return this->model_matrix;
}

void Particle::scale(const float &factor){
    this->model_matrix[0][0] *= factor;
    this->model_matrix[1][1] *= factor;
    this->model_matrix[2][2] *= factor;
}

void Particle::translate(const glm::vec3 &new_pos){
    this->model_matrix[3] = glm::vec4(new_pos, 1.0f);;
}

glm::vec4 Particle::get_translation() const {
    return this->model_matrix[3];
}

glm::quat Particle::get_rotation() const {

    glm::mat3 rot_scl = glm::mat3(this->model_matrix);

    glm::vec3 scale; // remove scale component
    scale.x = glm::length(rot_scl[0]);
    scale.y = glm::length(rot_scl[1]);
    scale.z = glm::length(rot_scl[2]);

    glm::mat3 rot;
    rot[0] = rot[0] / scale.x;
    rot[1] = rot[1] / scale.y;
    rot[2] = rot[2] / scale.z;

    glm::quat q = glm::quat_cast(rot);
    
    return q;
}

float Particle::get_scale() const {
    return glm::length(glm::mat3(this->model_matrix)[0]);
}

void Particle::set_color(glm::vec3 color){
    this->color = color;
}

glm::vec3 Particle::get_color(){
    return this->color;
}

void Particle::set_colliding(bool value){
    this->colliding = value;
}

bool Particle::is_colliding(){
    return this->colliding;
}

