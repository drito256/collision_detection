#include "../include/app/plane.h"


Plane::Plane(glm::vec3 position, float scale) : scale{scale}, position{position}{


    std::vector<Vertex> vertices{
    Vertex{.pos = glm::vec3{1, 0.f,  1} * scale, .norm = glm::vec3(0, 1, 0)},
    Vertex{.pos = glm::vec3{1, 0.f, -1} * scale, .norm = glm::vec3(0, 1, 0)},
    Vertex{.pos = glm::vec3{-1, 0.f,  1} * scale, .norm = glm::vec3(0, 1, 0)},

    Vertex{.pos = glm::vec3{-1, 0.f,  1} * scale, .norm = glm::vec3(0, 1, 0)},
    Vertex{.pos = glm::vec3{1, 0.f, -1} * scale, .norm = glm::vec3(0, 1, 0)},
    Vertex{.pos = glm::vec3{-1, 0.f, -1} * scale, .norm = glm::vec3(0, 1, 0)}
};


    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);


    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3) * 2, vertices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 
                         (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                         (void*) offsetof(Vertex, norm));
    glEnableVertexAttribArray(1);



    glBindVertexArray(0);
}

void Plane::render(Shader s){
    glm::mat4 mat(1.0f);

    mat[3] = glm::vec4(this->position, 1.f);;

    s.use();
    s.setMat4("model", mat);
    s.setVec3("color", glm::vec3{0.5f, 0.2f, 0.5f});

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}


glm::vec3 Plane::get_position() const{
    return this->position;
}
