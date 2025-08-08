#ifndef SPATIAL_GRID_H
#define SPATIAL_GRID_H

#include "particle.h"
#include "cube.h"

#include <unordered_map>
#include <vector>
#include <array>


class SpatialGrid{
public:
    SpatialGrid(float cell_size);
    std::vector<std::pair<int, int>> find_collision_candidates(const std::vector<Particle> &vec);
    void render(Shader s);

private:
    float cell_size;
    const float diagonal_length = glm::sqrt(3.0f) * cell_size;
    const float combined_radius = diagonal_length;
    glm::ivec3 cell;
    std::unordered_map<int, std::vector<int>> grid; // keys - cells,
                                                    // values - particle id
    unsigned int vao;
    unsigned int vbo;
    Cube cube_mesh;
    
    void clear_grid();
    void fill_grid(const std::vector<Particle> &vec);
    int get_cell_key(glm::vec3 pos);
    int get_cell_key_from_grid_coords(glm::ivec3 pos);
    glm::ivec3 key_to_grid_coords(int key) const;
    glm::vec3 key_to_world_coords(int key) const;
    void check_cell_pair_collisions(const std::vector<int>& cell1_indices,
                                    const std::vector<int>& cell2_indices,
                                    const std::vector<Particle>& all_particles,
                                    std::vector<std::pair<int, int>>& pairs);
};

#endif
