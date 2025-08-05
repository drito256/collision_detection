#include "../include/app/spatial_grid.h"


void SpatialGrid::clear_grid(){
    this->grid.clear();
}

void SpatialGrid::fill_grid(const std::vector<Particle> &vec){

    for(int i = 0; i < vec.size(); i++){
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
//                        std::cout << "neki kurac" << std::endl;
                        check_cell_pair_collisions(particles, it->second, vec, pairs);
                    }
                }
            }
        }
    }
    
    return pairs;
}

int SpatialGrid::get_cell_key(glm::vec3 pos){
    // treba staviti u klasu
    float edge_length = 2.f * 0.25f;
    float diagonal_length = sqrt(3) * edge_length / 2;;
    float cell_size = diagonal_length * 2;
    int offset = 1000;

    int x = (int)std::floor(pos.x / cell_size);
    int y = (int)std::floor(pos.y / cell_size);
    int z = (int)std::floor(pos.z / cell_size);

    return (x + offset) + (y + offset) * 2000 + (z + offset) * 4000000;

}

int SpatialGrid::get_cell_key_from_grid_coords(glm::ivec3 grid_coords) {
    int offset = 1000;
    return (grid_coords.x + offset) + (grid_coords.y + offset) * 2000 + (grid_coords.z + offset) * 4000000;
}
glm::ivec3 SpatialGrid::key_to_grid_coords(int key) const {
        int offset = 1000;
        int x = key % 2000 - offset;
        int y = (key / 2000) % 2000 - offset;
        int z = key / 4000000 - offset;
        return glm::ivec3(x, y, z);
}

/*void SpatialGrid::check_cell_pair_collisions(
                                                std::vector<Particle> vec1,
                                                std::vector<Particle> vec2,
                                                std::vector<std::pair<int, int>> &pairs){
    float edge_length = 2.f * 0.25f;
    float diagonal_length = sqrt(3) * edge_length / 2;
    float combined_radius = diagonal_length * 2 * 2;
    for(int i = 0 ; i < vec1.size();i++){
        for(int j = 0; j < vec2.size();j++){
            if(glm::length(vec1[i].get_translation() - vec2[j].get_translation()) - combined_radius <= 0){
                std::cout << "ajomooo" << std::endl;
                pairs.emplace_back(i, j);
            }
        }
    }
}*/

void SpatialGrid::check_cell_pair_collisions(
    const std::vector<int>& cell1_indices,
    const std::vector<int>& cell2_indices,
    const std::vector<Particle>& all_particles,
    std::vector<std::pair<int, int>>& pairs) {
    
    float edge_length = 2.0f * 0.25f;
    float diagonal_length = sqrt(3.0f) * edge_length / 2.0f;
    float combined_radius = diagonal_length * 2.0f;
    
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
