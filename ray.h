#include "vector3.h"

#ifndef RAY_H
#define RAY_H

class Ray
{
    public:
        Ray(){ origin = Vec3f(); direction = Vec3f(); }
        Ray(Vec3f origin, Vec3f direction){ this->origin = origin; this->direction = direction; }
        Vec3f getOrigin(){ return origin; }
        Vec3f getDirection(){ return direction; }
        Vec3f getReflection(Vec3f& normal)
        { 
            Vec3f v = (direction - origin);
            return v - normal.normalize()*2*(v.dot(normal.normalize()));
        }
    private:
        Vec3f origin, direction;
};

#endif