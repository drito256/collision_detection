#include "../include/app/plane.h"


Plane::Plane(float scale) : scale{scale}{


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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) offsetof(Vertex, norm));
    glEnableVertexAttribArray(1);



    glBindVertexArray(0);
}

void Plane::render(Shader s){
    glm::mat4 mat(1.0f);

    s.use();
    s.setMat4("model", mat);
    s.setVec3("objectColor", glm::vec3{1.0f,1.0f,0.9f});

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
