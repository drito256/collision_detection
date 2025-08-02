#include "../include/app/particle_sys.h"
#include <random>



ParticleSystem::ParticleSystem(glm::vec3 position, int count) : 
                                position{position},
                                count{count},
                                vertices{
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

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    

   glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
            vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 
                          (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 
                          (void*)offsetof(Vertex, norm));
    glEnableVertexAttribArray(1);



    glBindVertexArray(0);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0, 0.5f);
    std::uniform_real_distribution<> dist2(10.f, 15.f);


    std::uniform_real_distribution<> dist_rot1(0.f, 1.f);
    std::uniform_real_distribution<> dist_rot2(0.f, 1.f);
    std::uniform_real_distribution<> dist_rot3(0.f, 1.f);
    std::uniform_real_distribution<> dist_angle(0.f, 10.f);

    for(int i = 0; i < count; i++){
        glm::vec3 init_vel = {dist(gen), dist2(gen), dist(gen)};
        glm::vec3 init_rot = {dist_rot1(gen), dist_rot2(gen), dist_rot3(gen),};
        float angle = glm::radians(dist_angle(gen));
        glm::mat4 mat{1.0f};

        Particle p{mat, init_vel, init_rot, angle};
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
    s.setVec3("objectColor", glm::vec3(0.2f, 0.1f, 0.8f));
    for(int i = 0; i < particles.size(); i++){
        s.setMat4("model", particles[i].get_model());
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }

    glBindVertexArray(0);
}

void ParticleSystem::update(float dt){
    for(int i = 0; i < particles.size(); i++){
        particles[i].update(dt);
   }
}

std::vector<Particle> ParticleSystem::get_particles() const {
    return this->particles;
}
