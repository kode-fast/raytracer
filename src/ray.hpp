#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray{
    public:
    ray() {}
    ray(const point3 &origin, const vec3 &direction) : orig(origin) , dir(direction) {}

    // return unmodifiable pointer to varuables
    const point3& origin() const  { return orig; }
    const vec3& direction() const { return dir; }

    point3 pos(double t){
        return orig + (dir * t);
    }



    private:

    point3 orig;
    vec3 dir;
};

#endif