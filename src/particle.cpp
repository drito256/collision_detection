#include "../include/app/particle.h"


Particle::Particle(glm::mat4 model_matrix, glm::vec3 initial_velocity,
                   glm::vec3 initial_rotation, float angle) :
                model_matrix{model_matrix},
                initial_velocity{initial_velocity},
                initial_rotation{initial_rotation},
                angle{angle}
                {};

void Particle::update(const float &dt){
    const float gravity = 9.81f;
    glm::vec4 translation = get_translation(this->model_matrix);
    
    if(translation.y > 1 * get_scale(this->model_matrix) * sqrt(3)){
        translation =  translation + (glm::vec4(0.f, -gravity * dt * dt / 2.f, 0.f, 0.f) + 
                              glm::vec4(initial_velocity * dt, 0.0)) / 200.f;

        this->model_matrix = glm::rotate(this->model_matrix, angle, glm::normalize(initial_rotation));
        this->model_matrix[3] = translation;
    }
}

glm::mat4 Particle::get_model(){
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

glm::vec4 Particle::get_translation(const glm::mat4 &mat){
    return mat[3];
}

glm::quat Particle::get_rotation(const glm::mat4 &mat){

    glm::mat3 rot_scl = glm::mat3(mat);

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

float Particle::get_scale(const glm::mat4 &mat){
    return glm::length(glm::mat3(mat)[0]);
}

//TODO
bool Particle::check_collision(const Particle &p){

    return true;
}


