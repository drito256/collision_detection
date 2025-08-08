#include "../include/app/cube.h"


Cube::Cube() : vertices{
                                    // Front face (Z = +1)
                                    Vertex{.pos = {-1, -1,  1}, .norm = { 0,  0,  1}},
                                    Vertex{.pos = { 1, -1,  1}, .norm = { 0,  0,  1}},
                                    Vertex{.pos = { 1,  1,  1}, .norm = { 0,  0,  1}},
                                    Vertex{.pos = { 1,  1,  1}, .norm = { 0,  0,  1}},
                                    Vertex{.pos = {-1,  1,  1}, .norm = { 0,  0,  1}},
                                    Vertex{.pos = {-1, -1,  1}, .norm = { 0,  0,  1}},

                                    // Back face (Z = -1)
                                    Vertex{.pos = { 1, -1, -1}, .norm = { 0,  0, -1}},
                                    Vertex{.pos = {-1, -1, -1}, .norm = { 0,  0, -1}},
                                    Vertex{.pos = {-1,  1, -1}, .norm = { 0,  0, -1}},
                                    Vertex{.pos = {-1,  1, -1}, .norm = { 0,  0, -1}},
                                    Vertex{.pos = { 1,  1, -1}, .norm = { 0,  0, -1}},
                                    Vertex{.pos = { 1, -1, -1}, .norm = { 0,  0, -1}},

                                    // Left face (X = -1)
                                    Vertex{.pos = {-1, -1, -1}, .norm = {-1,  0,  0}},
                                    Vertex{.pos = {-1, -1,  1}, .norm = {-1,  0,  0}},
                                    Vertex{.pos = {-1,  1,  1}, .norm = {-1,  0,  0}},
                                    Vertex{.pos = {-1,  1,  1}, .norm = {-1,  0,  0}},
                                    Vertex{.pos = {-1,  1, -1}, .norm = {-1,  0,  0}},
                                    Vertex{.pos = {-1, -1, -1}, .norm = {-1,  0,  0}},

                                    // Right face (X = +1)
                                    Vertex{.pos = { 1, -1,  1}, .norm = { 1,  0,  0}},
                                    Vertex{.pos = { 1, -1, -1}, .norm = { 1,  0,  0}},
                                    Vertex{.pos = { 1,  1, -1}, .norm = { 1,  0,  0}},
                                    Vertex{.pos = { 1,  1, -1}, .norm = { 1,  0,  0}},
                                    Vertex{.pos = { 1,  1,  1}, .norm = { 1,  0,  0}},
                                    Vertex{.pos = { 1, -1,  1}, .norm = { 1,  0,  0}},

                                    // Bottom face (Y = -1)
                                    Vertex{.pos = {-1, -1, -1}, .norm = { 0, -1,  0}},
                                    Vertex{.pos = { 1, -1, -1}, .norm = { 0, -1,  0}},
                                    Vertex{.pos = { 1, -1,  1}, .norm = { 0, -1,  0}},
                                    Vertex{.pos = { 1, -1,  1}, .norm = { 0, -1,  0}},
                                    Vertex{.pos = {-1, -1,  1}, .norm = { 0, -1,  0}},
                                    Vertex{.pos = {-1, -1, -1}, .norm = { 0, -1,  0}},

                                    // Top face (Y = +1)
                                    Vertex{.pos = {-1,  1,  1}, .norm = { 0,  1,  0}},
                                    Vertex{.pos = { 1,  1,  1}, .norm = { 0,  1,  0}},
                                    Vertex{.pos = { 1,  1, -1}, .norm = { 0,  1,  0}},
                                    Vertex{.pos = { 1,  1, -1}, .norm = { 0,  1,  0}},
                                    Vertex{.pos = {-1,  1, -1}, .norm = { 0,  1,  0}},
                                    Vertex{.pos = {-1,  1,  1}, .norm = { 0,  1,  0}},
                                }
    {
    glCreateVertexArrays(1, &this->vao);
    glCreateBuffers(1, &this->vbo);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), vertices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 
                          (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 
                          (void*) offsetof(Vertex, norm));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}


unsigned int Cube::getVAO(){
    return this->vao;
}

std::array<Vertex, 36> Cube::get_vertices(){
    return this->vertices;
}
