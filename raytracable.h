#include "ray.h"
#include "vector3.h"
#include "material.h"

#ifndef RAYTRACABLE_H
#define RAYTRACABLE_H

enum class IntersectionStatus{MISS, HIT, INSIDE};

class Raytracable
{
    public:
        virtual IntersectionStatus intersects(Ray ray, float near, float far, Vec3f &iPoint) = 0;
        virtual Vec3f getColor() = 0;
        virtual Vec3f getNormalForPoint(Vec3f point) = 0;
        virtual Material getMaterial(){ return material; }
        virtual void setMaterial(Material &m){ material = m; }
        virtual ~Raytracable(){}
    private:
        Material material;
};

#endif