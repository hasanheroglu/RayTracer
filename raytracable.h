#include "ray.h"
#include "vector3.h"

#ifndef RAYTRACABLE_H
#define RAYTRACABLE_H

enum class IntersectionStatus{MISS, HIT, INSIDE};

class Raytracable
{
    public:
        virtual IntersectionStatus intersects(Ray ray, float near, float far, Vec3f &iPoint) = 0;
        virtual Vec3f getColor() = 0;
        virtual Vec3f getNormalForPoint(Vec3f point) = 0;
        virtual ~Raytracable(){}
};

#endif