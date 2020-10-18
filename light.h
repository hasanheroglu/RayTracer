#include "vector3.h"
#include "ray.h"
#include "raytracable.h"
#include <vector>

#ifndef LIGHT_H
#define LIGHT_H

class Light
{
    public:
        Light(): intensity(1.0f),
                diffuseCoefficient(1.0f), ambientCoefficient(1.0f), specularCoefficient(1.0f),
                position(Vec3f(0.0f, 0.0f, 0.0f)), direction(Vec3f(0.0f, 0.0f, 1.0f)), color(Vec3f(1.0f, 1.0f, 1.0f)){}
        Light(float intensity,
            float diffuseCoefficient, float ambientCoefficient, float specularCoefficient,
            Vec3f position, Vec3f direction, Vec3f color): 
            intensity(intensity), 
            diffuseCoefficient(diffuseCoefficient), ambientCoefficient(ambientCoefficient), specularCoefficient(specularCoefficient),
            position(position), direction(direction), color(color){}
        float getIntensity(){ return intensity; }
        float getDiffuseCoefficient(){ return diffuseCoefficient; }
        float getAmbientCoefficient(){ return ambientCoefficient; }
        float getSpecularCoefficient(){ return specularCoefficient; }
        Vec3f getPosition(){ return position; }
        bool canSee(Vec3f point, std::vector<Raytracable*> &raytracables)
        {
            Ray ray(point, (position-point).normalize());

            for(size_t i=0; i<raytracables.size(); i++)
            {
                Vec3f iPoint;
                if(raytracables[i]->intersects(ray, 0.1f, 100.0f, iPoint) == IntersectionStatus::HIT)
                {
                    return false;
                }
            }

            return true;
        }
    private:
        float intensity, diffuseCoefficient, ambientCoefficient, specularCoefficient;
        Vec3f position;
        Vec3f direction;
        Vec3f color;
};

#endif