#include "../include/app/collision_sys.h"


bool collision_sys::check_collision(const Particle &p, const Plane &pl){
    float diagonal_length = p.get_scale() * sqrt(3) / 2.f;

    if(p.get_translation().y - diagonal_length > pl.get_position().y)
        return true;

    return false;
}

int collision_sys::check_collision(const std::vector<Particle> &v, const Plane &pl){
    for(size_t i = 0; i < v.size(); i++){
        if(check_collision(v[i], pl)){
//            std::cout << "Collision occured " << i <<  std::endl;
            //return i;
        }
    }
    return -1;
}

bool collision_sys::check_collision(const Particle &p1, const Particle &p2){
    // potreban SAT algo

    std::vector<glm::vec3> axis;
    
    std::array<glm::vec3, 3> p1_axis = get_axis(p1.get_model());
    std::array<glm::vec3, 3> p2_axis = get_axis(p2.get_model());

    for(size_t i = 0; i < p1_axis.size(); i++){
        axis.push_back(p1_axis[i]);
    }
    for(size_t i = 0; i < p2_axis.size(); i++){
        axis.push_back(p2_axis[i]);
    }

    for(size_t i = 0; i < p1_axis.size() ; i++){
        for(size_t j = 0; j < p2_axis.size(); j++){
            glm::vec3 cross = glm::cross(p1_axis[i], p2_axis[j]);
            if(cross.length() > Physics::sat_epsilon){
                axis.push_back(glm::normalize(cross));
            }
        }
    }

    for(glm::vec3 a : axis){
        std::pair<float, float> interval1 = project_onto_axis(p1, a);
        std::pair<float, float> interval2 = project_onto_axis(p2, a);

        if(interval1.second < interval2.first || interval2.second < interval1.first){
            return false;
        }
    }

    return true;
}

std::vector<std::pair<int, int>> collision_sys::check_collision(const std::vector<Particle> &v){
    std::vector<std::pair<int, int>> collision_pair_vec;
    collision_pair_vec.reserve(v.size());

    for(size_t i = 0; i < v.size(); i++){
        for(size_t j = i + 1; j < v.size(); j++){
            if(check_collision(v[i], v[j])){
                collision_pair_vec.emplace_back(i, j);
            }
        }
    }
    return collision_pair_vec;
}

std::array<glm::vec3, 3> collision_sys::get_axis(const glm::mat4 &model){
    glm::mat3 mat = glm::mat3(model);
    std::array<glm::vec3 , 3> axis;

    axis[0] = glm::normalize(glm::vec3(mat[0]));
    axis[1] = glm::normalize(glm::vec3(mat[1]));
    axis[2] = glm::normalize(glm::vec3(mat[2]));

    return axis;
};

std::pair<float, float> collision_sys::project_onto_axis(const Particle &p, 
                                                         const glm::vec3 &axis) {
    float radius = 0.f;
    
    std::array<glm::vec3, 3> cube_axis = get_axis(p.get_model());
    
    float half_extent = p.get_scale();
    
    for(int i = 0; i < 3; i++) {
        radius += glm::abs(glm::dot(cube_axis[i], axis)) * half_extent;
    }
    
    glm::vec3 position = p.get_translation();
    float center = glm::dot(position, axis);
    
    return std::make_pair(center - radius, center + radius);
}
