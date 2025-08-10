#include "../include/app/particle_sys.h"
#include <random>


ParticleSystem::ParticleSystem(glm::vec3 position, int count, std::pair<float, float> scale_range) : 
                                position{position},
                                count{count},
                                cube_mesh(Cube())
                               {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.f, 0.01f);
    std::uniform_real_distribution<> dist2(0.15f, 0.2f);


    std::uniform_real_distribution<> dist_rot_axis(0.f, 1.f);
    std::uniform_real_distribution<> dist_rot_angle(0.f, 2.f);
    std::uniform_real_distribution<> dist_color(0.5f, 0.8f);
    std::uniform_real_distribution<> dist_rev_radius(0.8f, 1.0f);
    std::uniform_real_distribution<> dist_rev_angle(0.0f, glm::pi<float>() * 2.f);
    std::uniform_real_distribution<> dist_ang_vel(0.005f, 0.01f);
    std::uniform_real_distribution<> dist_scale(scale_range.first, scale_range.second);

    for(int i = 0; i < count; i++){
        glm::vec3 init_rot = {dist_rot_axis(gen), dist_rot_axis(gen), dist_rot_axis(gen),};
        float rot_angle = glm::radians(dist_rot_angle(gen)); // rotation angle
        glm::mat4 mat{1.0f};


        float rev_angle = dist_rev_angle(gen); // revolution
        float rev_radius = dist_rev_radius(gen) * 10.f;
        float angular_velocity = dist_ang_vel(gen);

        Particle p{mat, init_rot, rot_angle, rev_angle, rev_radius, angular_velocity};

        p.translate(position);

        p.scale(dist_scale(gen));
        p.set_color(glm::vec3(dist_color(gen)));
        p.set_colliding(false);

        particles.push_back(p);
    }
}

void ParticleSystem::render(Shader s){
    glBindVertexArray(cube_mesh.getVAO());
    
    s.use();
    for(size_t i = 0; i < particles.size(); i++){
        s.setMat4("model", particles[i].get_model());
        if(particles[i].is_colliding()){
            s.setVec3("color", glm::vec3(0.8f, 0.f, 0.f));
        }
        else{
            s.setVec3("color", particles[i].get_color());
        }
        glDrawArrays(GL_TRIANGLES, 0, (cube_mesh.get_vertices()).size());
    }

    glBindVertexArray(0);
}

void ParticleSystem::update(float dt){
    for(size_t i = 0; i < particles.size(); i++){
        particles[i].update(dt);
   }
}

std::vector<Particle>& ParticleSystem::get_particles(){
    return this->particles;
}
