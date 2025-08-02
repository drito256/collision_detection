#include "../include/app/collision_sys.h"


bool collision_sys::check_collision(const Particle &p, const Plane &pl){
    glm::mat4 p_model_mat = p.get_model();
    float diagonal_length = p.get_scale(p_model_mat) * sqrt(3) / 2.f;

    if(p.get_translation(p_model_mat).y - diagonal_length > pl.get_position().y)
        return true;

    return false;
}

int collision_sys::check_collision(const std::vector<Particle> &v, const Plane &pl){
    for(int i = 0; i < v.size(); i++){
        if(check_collision(v[i], pl)){
            std::cout << "Collision occured " << i <<  std::endl;
            //return i;
        }
    }
    return -1;
}

bool collision_sys::check_collision(const Particle &p1, const Particle &p2){
    // potreban SAT algo

    return false;
}

std::pair<int,int> collision_sys::check_collision(const std::vector<Particle> &v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size(); j++){
            if(i != j){
                if(check_collision(v[i], v[j])){
                    std::cout << "Collision occured " << i <<  std::endl;
                    //return std::make_pair(i,j);
                }
            }
        }
    }
    return std::make_pair(-1, -1);
}


