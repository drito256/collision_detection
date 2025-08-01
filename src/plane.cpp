#include "../include/app/plane.h"


Plane::Plane(float scale) : scale{scale}{


    std::vector<glm::vec3> vertices = {
        glm::vec3{1,0.f,-1} * scale,
        glm::vec3{1,0.f,1} * scale,
        glm::vec3{-1,0.f,1} * scale,

        glm::vec3{-1,0.f,1} * scale,
        glm::vec3{-1,0.f,-1} * scale,
        glm::vec3{1,0.f,-1} * scale,

    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);


    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Plane::render(Shader s){
    glm::mat4 mat(1.0f);

    s.use();
    s.setMat4("model", mat);
    s.setVec3("color", glm::vec3{1.0f,1.0f,0.9f});

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
