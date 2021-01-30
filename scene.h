#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdio>
#include "vector3.h"
#include "raytracable.h"
#include "light.h"
#include "camera.h"

#define NEAR 0.1
#define FAR 100
#define PI 3.14

#ifndef SCENE_H
#define SCENE_H

struct Position2D {
    float x;
    float y;

    Position2D(float x_, float y_) {
        x = x_;
        y = y_;
    }
};

class Scene{
    public:
        Scene(){}
        Scene(std::vector<Raytracable*> &objects, std::vector<Light*> &lights){ this->objects = objects; this->lights = lights; }
        
        Position2D getWorldPositionFromPixelPosition(Position2D pixelPosition, int width, int height, float fov) {
            float worldPosX = ((float)(2*pixelPosition.x - width)/width)*std::tan(3.14f/4.0f);
            float worldPosY = ((float)(2*pixelPosition.y - height)/height)*std::tan((height/width)*3.14f/4.0f);
            return Position2D(worldPosX, worldPosY);
        }

        void trace()
        {
            const int height = camera->getHeight();
            const int width = camera->getWidth();
            Vec3f origin = camera->getOrigin();

            float zBuffer[height][width];
            for(size_t i=0; i<height; i++)
            {
                for(size_t j=0; j<width; j++)
                {
                    zBuffer[i][j]= 99999.0f;
                }
            }

            std::ofstream img("picture.ppm");
            img << "P3" << std::endl;
            img << width << " " << height << std::endl;
            img << "255" << std::endl;

            for(int y=height-1; y>=0; y--)
            {
                for(int x=0; x<width; x++)
                {
                    Position2D worldPosition = getWorldPositionFromPixelPosition(Position2D(x, y), width, height, PI/4);
                    Ray ray(origin, (Vec3f(worldPosition.x, worldPosition.y, 1.0f)).normalize());
                    Vec3f currentColor(0.5f, 0.5f, 0.5f);            
                    
                    for(size_t i=0; i<objects.size(); i++)
                    {
                        Vec3f iPoint;
                        if(objects[i]->intersects(ray, NEAR, FAR, iPoint) == IntersectionStatus::HIT)
                        {                    
                            if(iPoint.z < zBuffer[y][x])
                            {
                                zBuffer[y][x] = iPoint.z;
                                //currentColor = objects[i]->getColor();

                                for(size_t j=0; j<lights.size(); j++)
                                {
                                    //TODO
                                    //Will not work with multiple lights colors will be overriden
                                    if(lights[j]->canSee(iPoint, objects))
                                    {
                                        Vec3f diffuseColor = objects[i]->getMaterial().getDiffuseColor()*lights[j]->getColor()*getDiffuseColorCoefficient(objects[i], lights[j], iPoint);
                                        Vec3f ambientColor = objects[i]->getMaterial().getAmbientColor()*lights[j]->getColor();
                                        Vec3f specularColor = objects[i]->getMaterial().getSpecularColor()*lights[j]->getSpecularCoefficient()*std::pow(getSpecularColorCoefficient(objects[i], lights[j], iPoint), objects[i]->getMaterial().getShininess());
                                        currentColor =  diffuseColor + ambientColor + specularColor;
                                    }
                                    else
                                    {
                                        Vec3f ambientColor = objects[i]->getColor()*lights[j]->getAmbientCoefficient();
                                        currentColor =  ambientColor;
                                    }
                                }
                            }
                        } 
                    }
                    
                    clampColor(currentColor);
                    img << (int) (currentColor.x * 255)  << " " << (int) (currentColor.y * 255) << " " << (int) (currentColor.z * 255)  << std::endl;
                }
            }
        }
        void addObject(Raytracable* o){ objects.push_back(o); }
        void addLight(Light* l) { lights.push_back(l); }
        void setCamera(Camera* c) { camera = c; }
    private:
        std::vector<Raytracable*> objects;
        std::vector<Light*> lights;
        //TODO: allow multiple cameras?
        Camera* camera;

        void clampColor(Vec3f &color)
        {
            if(color.x > 1) color.x = 1.0f;
            if(color.y > 1) color.y = 1.0f;
            if(color.z > 1) color.z = 1.0f;
        }

        float getDiffuseColorCoefficient(Raytracable* raytracable, Light* light, Vec3f intersectionPoint)
        {
            //normal
            Vec3f n = raytracable->getNormalForPoint(intersectionPoint).normalize();
            //direction to the light
            Vec3f l = (light->getPosition()-intersectionPoint).normalize();
            float d = n.dot(l);
            if(d<0){ d=0; }
            return d;
        }

        float getSpecularColorCoefficient(Raytracable* raytracable, Light* light, Vec3f intersectionPoint)
        {
            Ray lightRay = Ray(light->getPosition(), (intersectionPoint - light->getPosition()).normalize()); 
            Vec3f n = raytracable->getNormalForPoint(intersectionPoint).normalize();
            Vec3f r = lightRay.getReflection(n);
            Vec3f v = (camera->getOrigin() - intersectionPoint);
            float s = v.normalize().dot(r.normalize());
            if(s<0){ s=0; }
            return s;
        }
};

#endif 

