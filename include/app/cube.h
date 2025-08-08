#ifndef CUBE_H
#define CUBE_H


#include "vertex.h"

#include <array>

class Cube{
public:
    Cube();
    unsigned int getVAO();
    std::array<Vertex, 36> get_vertices();

private:
    float scale;
    glm::vec3 position;
    unsigned int vao;
    unsigned int vbo;
    std::array<Vertex, 36> vertices;
};

#endif
