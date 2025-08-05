#ifndef COLLISION_SYS_H
#define COLLISION_SYS_H

#include "particle.h"
#include "plane.h"

#include <array>

class collision_sys{
public:
    static bool check_collision(const Particle &p, const Plane &pl);
    static bool check_collision(const Particle &p1, const Particle &p2);
    static int check_collision(const std::vector<Particle> &vec, const Plane &pl);
    static std::vector<std::pair<int, int>> check_collision(const std::vector<Particle> &vec);

private:
    static std::array<glm::vec3, 3> get_axis(const glm::mat4 &model);
    static std::pair<float, float> project_onto_axis(const Particle &p, 
                                                     const glm::vec3 &axis);


};





#endif
