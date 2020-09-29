#include "ray.h"
#include "vector3.h"

#ifndef RAYTRACABLE_H
#define RAYTRACABLE_H

class Raytracable
{
    public:
        virtual bool intersects(Ray ray, float near, float far, float &zPoint) = 0;
        virtual Vec3f getColor() = 0;
        virtual ~Raytracable(){};
};


#endif