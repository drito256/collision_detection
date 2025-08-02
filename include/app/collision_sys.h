#ifndef COLLISION_SYS_H
#define COLLISION_SYS_H

#include "particle.h"
#include "plane.h"

class collision_sys{
public:
    static bool check_collision(const Particle &p, const Plane &pl);
    static bool check_collision(const Particle &p1, const Particle &p2);
    static int check_collision(const std::vector<Particle> &vec, const Plane &pl);
    static std::pair<int, int> check_collision(const std::vector<Particle> &vec);

private:


};





#endif
