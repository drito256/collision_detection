#include "../include/app/particle.h"


Particle::Particle(glm::mat4 model_matrix, glm::vec3 initial_velocity) :
                model_matrix{model_matrix},
                initial_velocity{initial_velocity}
                {};

void Particle::update(){
    this->model_matrix[3] += glm::vec4(initial_velocity, 0.0);
}

glm::mat4 Particle::get_model(){
    return this->model_matrix;
}

void Particle::scale(float factor){
    this->model_matrix[0][0] *= factor;
    this->model_matrix[1][1] *= factor;
    this->model_matrix[2][2] *= factor;
}

void Particle::translate(glm::vec3 new_pos){
    this->model_matrix[3] = glm::vec4(new_pos, 1.0f);;
}
