#ifndef SPHERE_H
#define SPHERE_H

#include "../glm/glm.hpp"

class Sphere{
public:
    Sphere(glm::vec3 coordinate, glm::vec3 velocity, double radius);
    glm::vec3 get_coordinate();
    glm::vec3 get_velocity();
    double get_radius();

    void update();

private:
    glm::vec3 coordinate;
    glm::vec3 velocity;
    double radius;
};


#endif
