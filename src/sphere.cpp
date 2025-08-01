#include "../include/app/sphere.h"


Sphere::Sphere(glm::vec3 coordinate, glm::vec3 velocity, float radius) : coordinate{coordinate}, 
                                                                          velocity{velocity},
                                                                          radius{radius}
                                                                          {
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    
    Vertex vertex{coordinate, radius};
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &vertex , GL_DYNAMIC_DRAW);
   
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)offsetof(Vertex, coordinate));
    glEnableVertexAttribArray(0);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float), &vertex, GL_DYNAMIC_DRAW);
   
    glVertexAttribPointer(1,1,GL_FLOAT, GL_FALSE, sizeof(double), (void*)offsetof(Vertex, radius));
    glEnableVertexAttribArray(1);
    

    
    glBindVertexArray(0);
}

float Sphere::get_radius(){
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



