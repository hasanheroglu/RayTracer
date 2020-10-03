#include <cstdio>
#include <algorithm>
#include "vector3.h"
#include "ray.h"
#include "raytracable.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle: public Raytracable
{
    public:
        Triangle(){ p1 = Vec3f(); p2 = Vec3f(); p3 = Vec3f(); color = Vec3f(); }
        Triangle(Vec3f p1, Vec3f p2, Vec3f p3, Vec3f color){ this->p1 = p1; this->p2 = p2; this->p3 = p3; this->color = color;}
        void print(){ printf("\nPoints:\n"); p1.print(); p2.print(); p3.print(); printf("\nColor:\n"); color.print(); }
        Vec3f getColor(){ return color; }
        Vec3f getNormal(){ return (p1-p2).cross(p1-p3); }
        Vec3f getNormalForPoint(Vec3f point){ return (point-p1).cross(point-2); }
        float getMinX(){ return std::min(p1.x, std::min(p2.x, p3.x)); }
        float getMinY(){ return std::min(p1.y, std::min(p2.y, p3.y)); }
        float getMinZ(){ return std::min(p1.z, std::min(p2.z, p3.z)); }
        float getMaxX(){ return std::max(p1.x, std::max(p2.x, p3.x)); }
        float getMaxY(){ return std::max(p1.y, std::max(p2.y, p3.y)); } 
        float getMaxZ(){ return std::max(p1.z, std::max(p2.z, p3.z)); }
        float getPlaneConstant(){ return -p1.dot(getNormal()); }
        IntersectionStatus intersects(Ray ray, float near, float far, Vec3f &iPoint)
        {
            float lambda = -(ray.getOrigin().dot(getNormal()) + getPlaneConstant())/(ray.getDirection().dot(getNormal()));
            if(lambda < 0) return IntersectionStatus::MISS;

            Vec3f intersectionPoint = ray.getOrigin() + ray.getDirection()*lambda;
            float distance = (intersectionPoint - ray.getOrigin()).norm();
            if(distance<near || distance>=far) return IntersectionStatus::MISS;

            iPoint = intersectionPoint;
            if(intersectionPoint.x > getMaxX() || intersectionPoint.x < getMinX()) return IntersectionStatus::MISS;
            if(intersectionPoint.y > getMaxY() || intersectionPoint.y < getMinY()) return IntersectionStatus::MISS;
            if(intersectionPoint.z > getMaxZ() || intersectionPoint.z < getMinZ()) return IntersectionStatus::MISS;


            //TO DO
            //write a function for calculations below
            Vec3f v = p2-p3;
            Vec3f a = v.cross(intersectionPoint - p3);
            Vec3f b = v.cross(p1 - p3);
            float c = a.dot(b);
            if(c < 0) return IntersectionStatus::MISS;

            v = p1-p3;
            a = v.cross(intersectionPoint - p3);
            b = v.cross(p2 - p3);
            c = a.dot(b);
            if(c < 0) return IntersectionStatus::MISS;

            v = p1-p2;
            a = v.cross(intersectionPoint - p2);
            b = v.cross(p3 - p2);
            c = a.dot(b);
            if(c < 0) return IntersectionStatus::MISS;

            return IntersectionStatus::HIT;
        }
    private:
        Vec3f p1, p2, p3;
        Vec3f color;
};

#endif