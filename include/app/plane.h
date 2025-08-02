#ifndef PLANE_H
#define PLANE_H

#include "../glad/glad.h"
#include "vertex.h"

#include <vector>

class Plane{
public:
    Plane(glm::vec3 position, float scale);
    void render(Shader s);

    glm::vec3 get_position() const;

private:
    float scale;
    glm::vec3 position;

    unsigned int vao;
    unsigned int vbo;

};






#endif
