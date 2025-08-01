#include "../include/app/particle_sys.h"
#include <random>



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
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-0.5f, 0.5f);
    std::uniform_real_distribution<> dist2(5.f, 10.f);
    for(int i = 0; i < count; i++){
        glm::vec3 init_vel = {dist(gen), dist2(gen), dist(gen)};
        glm::mat4 mat{1.0f};

        Particle p{mat, init_vel};
        p.translate(position);
        p.scale(0.1f);

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
    s.setVec3("color", glm::vec3(0.2f, 0.1f, 0.8f));
    for(int i = 0; i < particles.size(); i++){
        s.setMat4("model", particles[i].get_model());
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
}

void ParticleSystem::update(float dt){
    for(int i = 0; i < particles.size(); i++){
        particles[i].update(dt);
    }
}
