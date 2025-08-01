#ifndef PLANE_H
#define PLANE_H

#include "../glad/glad.h"
#include "shader.h"

#include <vector>

class Plane{
public:
    Plane(float scale);
    void render(Shader s);



private:
    float scale;

    unsigned int vao;
    unsigned int vbo;

};






#endif
