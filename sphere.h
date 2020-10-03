#include <cstdio>
#include <cmath>
#include "vector3.h"
#include "ray.h"
#include "raytracable.h"

#ifndef SPHERE_H
#define SPHERE_H

class Sphere : public Raytracable
{
    public:
        Sphere(): center(Vec3f(0.0f)), radius(1.0f), color(Vec3f(1.0f)){};
        Sphere(Vec3f center, float radius, Vec3f color): center(center), radius(radius), color(color){};
        Vec3f getCenter(){ return center; }
        Vec3f getColor(){ return color; }
        float getRadius(){ return radius; }
        Vec3f getNormalForPoint(Vec3f point){ return (point-center).normalize(); }
        IntersectionStatus intersects(Ray ray, float near, float far, Vec3f &iPoint)
        {
            //line-sphere intersection equation variable calculations
            float a = ray.getDirection().norm2();
            float b = 2*(ray.getDirection().dot((ray.getOrigin() - center)));
            float c = (ray.getOrigin() - center).norm2() - pow(radius,2);
            float delta = pow(b,2) - 4*a*c;
            float distance;

            if(delta<0){ return IntersectionStatus::MISS; }
            else if(delta==0)
            {
                distance = -b/(2*a); 
            }
            else
            {
                float temp = (-b + sqrt(delta))/(2*a);
                distance = (-b - sqrt(delta))/(2*a);
                if(distance > temp){ distance = temp; }
            }

            //sphere is behind the camera
            if(distance<near || distance>=far){ return IntersectionStatus::MISS; }


            Vec3f intersectionPoint = ray.getOrigin() + ray.getDirection()*distance;
            iPoint = intersectionPoint;
            return IntersectionStatus::HIT;
        }
    private:
        Vec3f center, color;
        float radius;
};

#endif