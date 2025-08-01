#include "../include/app/sphere.h"


Sphere::Sphere(glm::vec3 coordinate, glm::vec3 velocity, double radius) : coordinate{coordinate}, 
                                                                          velocity{velocity},
                                                                          radius{radius}
                                                                          {}

double Sphere::get_radius(){
    return this->radius;
}

glm::vec3 Sphere::get_coordinate(){
    return this->coordinate;
}

glm::vec3 Sphere::get_velocity(){
    return this->velocity;
}

void Sphere::update(){
    this->coordinate += this->velocity;
}



