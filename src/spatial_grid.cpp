#include "../include/app/spatial_grid.h"

SpatialGrid::SpatialGrid(float cell_size) : cell_size{cell_size},
                                            cube_mesh(Cube()){
}

void SpatialGrid::clear_grid(){
    this->grid.clear();
}

void SpatialGrid::fill_grid(const std::vector<Particle> &vec){

    for(size_t i = 0; i < vec.size(); i++){
        int key = get_cell_key(vec[i].get_translation());
        this->grid[key].push_back(i);
    }

}

std::vector<std::pair<int, int>> SpatialGrid::find_collision_candidates(const std::vector<Particle> &vec){
    std::vector<std::pair<int, int>> pairs;
    
    clear_grid();
    fill_grid(vec);

    for(const auto& [cell_key, particles] : grid) {
        glm::ivec3 coords = key_to_grid_coords(cell_key);
        
        // Check current cell + all 26 neighbors  ==> treba skalirati dx,dy,dz
        for(int dx = -1; dx <= 1; dx+=1) {
            for(int dy = -1; dy <= 1; dy+=1) {
                for(int dz = -1; dz <= 1; dz+=1) {
                    glm::ivec3 neighbor_coords = coords + glm::ivec3(dx, dy, dz);
                    int neighbor_key = get_cell_key_from_grid_coords(neighbor_coords);
                    
                    auto it = grid.find(neighbor_key);
                    if(it != grid.end()) {
                        // Check collisions between current cell and neighbor
                        check_cell_pair_collisions(particles, it->second, vec, pairs);
                    }
                }
            }
        }
    }
    
    return pairs;
}

int SpatialGrid::get_cell_key(glm::vec3 pos){

    int x = (int)std::floor(pos.x / diagonal_length);
    int y = (int)std::floor(pos.y / diagonal_length);
    int z = (int)std::floor(pos.z / diagonal_length);

    return (x + offset) + (y + offset) * stride + (z + offset) * stride * stride;

}

int SpatialGrid::get_cell_key_from_grid_coords(glm::ivec3 grid_coords) {
    return (grid_coords.x + offset) + (grid_coords.y + offset) * stride + 
           (grid_coords.z + offset) * stride * stride;
}
glm::ivec3 SpatialGrid::key_to_grid_coords(int key) const {
        int x = key % stride - offset;
        int y = (key / stride) % stride - offset;
        int z = key / (stride * stride) - offset;
        return glm::ivec3(x, y, z);
}

glm::vec3 SpatialGrid::key_to_world_coords(int key) const {
    glm::ivec3 grid_coords = key_to_grid_coords(key);
    glm::vec3 world_pos;

    world_pos.x = grid_coords.x * diagonal_length;
    world_pos.y = grid_coords.y * diagonal_length;
    world_pos.z = grid_coords.z * diagonal_length;
    return world_pos;
}

void SpatialGrid::check_cell_pair_collisions(
    const std::vector<int>& cell1_indices,
    const std::vector<int>& cell2_indices,
    const std::vector<Particle>& all_particles,
    std::vector<std::pair<int, int>>& pairs) {
    
    for(int idx1 : cell1_indices) {
        for(int idx2 : cell2_indices) {
            // Avoid duplicates and self-collision
            if(idx1 >= idx2) continue;
            
            const Particle& p1 = all_particles[idx1];
            const Particle& p2 = all_particles[idx2];
            
            // Check bounding sphere collision
            float distance = glm::length(p1.get_translation() - p2.get_translation());
            if(distance <= combined_radius) {
                pairs.emplace_back(idx1, idx2);
            }
        }
    }
}

void SpatialGrid::render(Shader s){
    glBindVertexArray(this->cube_mesh.getVAO());
    s.use();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
    for(const auto& pair : grid){
        glm::mat4 mat(1.0f);
        
        glm::vec3 world_coords = key_to_world_coords(pair.first);
        world_coords += glm::vec3(diagonal_length * 0.5f);
        
        mat = glm::translate(mat, world_coords);
        mat = glm::scale(mat, glm::vec3(diagonal_length));
        
        s.setMat4("model", mat);
        s.setVec3("color", glm::vec3(0, 1, 0));
        glDrawArrays(GL_TRIANGLES, 0, (this->cube_mesh.get_vertices()).size());
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    glBindVertexArray(0);
}
