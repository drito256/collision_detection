#include "../include/app/particle_sys.h"



ParticleSystem::ParticleSystem(glm::vec3 position, int count) : 
                                position{position},
                                count{count},
                                vertices{
                                    Vertex{.pos = {-1, -1, -1}},
                                    Vertex{.pos = { 1, -1, -1}},
                                    Vertex{.pos = { 1,  1, -1}},
                                    Vertex{.pos = { 1,  1, -1}},
                                    Vertex{.pos = {-1,  1, -1}},
                                    Vertex{.pos = {-1, -1, -1}},

                                    Vertex{.pos = {-1, -1,  1}},
                                    Vertex{.pos = { 1, -1,  1}},
                                    Vertex{.pos = { 1,  1,  1}},
                                    Vertex{.pos = { 1,  1,  1}},
                                    Vertex{.pos = {-1,  1,  1}},
                                    Vertex{.pos = {-1, -1,  1}},

                                    Vertex{.pos = {-1,  1,  1}},
                                    Vertex{.pos = {-1,  1, -1}},
                                    Vertex{.pos = {-1, -1, -1}},
                                    Vertex{.pos = {-1, -1, -1}},
                                    Vertex{.pos = {-1, -1,  1}},
                                    Vertex{.pos = {-1,  1,  1}},

                                    Vertex{.pos = { 1,  1,  1}},
                                    Vertex{.pos = { 1,  1, -1}},
                                    Vertex{.pos = { 1, -1, -1}},
                                    Vertex{.pos = { 1, -1, -1}},
                                    Vertex{.pos = { 1, -1,  1}},
                                    Vertex{.pos = { 1,  1,  1}},

                                    Vertex{.pos = {-1, -1, -1}},
                                    Vertex{.pos = { 1, -1, -1}},
                                    Vertex{.pos = { 1, -1,  1}},
                                    Vertex{.pos = { 1, -1,  1}},
                                    Vertex{.pos = {-1, -1,  1}},
                                    Vertex{.pos = {-1, -1, -1}},

                                    Vertex{.pos = {-1,  1, -1}},
                                    Vertex{.pos = { 1,  1, -1}},
                                    Vertex{.pos = { 1,  1,  1}},
                                    Vertex{.pos = { 1,  1,  1}},
                                    Vertex{.pos = {-1,  1,  1}},
                                    Vertex{.pos = {-1,  1, -1}}
                               }
    {

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);


    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    

   glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
            vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 
                          (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    
    for(int i = 0; i < count; i++){
        glm::vec3 init_vel = {0, 1/100.f, 0};
        glm::mat4 mat{1.0f};

        Particle p{mat, init_vel};
        p.translate(position);
        p.scale(0.05f);

        particles.push_back(p);
    }
}

/*ParticleSystem::~ParticleSystem(){
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(GL_ARRAY_BUFFER, &vbo);
}*/

void ParticleSystem::render(Shader s){
    glBindVertexArray(vao);
    
    s.use();
    for(int i = 0; i < particles.size(); i++){
        s.setMat4("model", particles[i].get_model());
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
}

void ParticleSystem::update(){
    for(int i = 0; i < particles.size(); i++){
        particles[i].update();
    }
}
