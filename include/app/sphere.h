#ifndef SPHERE_H
#define SPHERE_H

#include "../glm/glm.hpp"
#include "../glad/glad.h"

class Sphere{
public:
    Sphere(glm::vec3 coordinate, glm::vec3 velocity, float radius);
    glm::vec3 get_coordinate();
    glm::vec3 get_velocity();
    float get_radius();

    void update();
    void render();

private:
    glm::vec3 coordinate;
    glm::vec3 velocity;
    float radius;

    unsigned int vao;
    unsigned int vbo;
};

struct Vertex{
    glm::vec3 coordinate;
    float radius;
};

#endif
