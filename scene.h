#include <iostream>
#include <fstream>
#include <vector>
#include "vector3.h"
#include "raytracable.h"
#include "light.h"

#define NEAR 0.1
#define FAR 100

#ifndef SCENE_H
#define SCENE_H
class Scene{
    public:
        Scene(){}
        Scene(std::vector<Raytracable*> &objects, std::vector<Light*> &lights){ this->objects = objects; this->lights = lights; }
        
        void trace(int width, int height, Vec3f origin)
        {
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

            for(int x=height/2 - 1; x>=-height/2; x--)
            {
                for(int y=-width/2; y<width/2; y++)
                {
                    Ray ray(origin, (Vec3f((float)y/(height/2), (float)x/(height/2), 1.0f)-origin).normalize());
                    Vec3f currentColor(0.5f, 0.5f, 0.5f);            
                    
                    for(size_t i=0; i<objects.size(); i++)
                    {
                        Vec3f iPoint;
                        if(objects[i]->intersects(ray, NEAR, FAR, iPoint) == IntersectionStatus::HIT)
                        {                    
                            if(iPoint.z < zBuffer[x+height/2][y+width/2])
                            {
                                zBuffer[x+height/2][y+width/2] = iPoint.z;
                                //currentColor = objects[i]->getColor();

                                for(size_t j=0; j<lights.size(); j++)
                                {
                                    //TODO
                                    //Will not work with multiple lights colors will be overriden
                                    if(lights[j]->canSee(iPoint, objects))
                                    {
                                        //normal
                                        Vec3f n = objects[i]->getNormalForPoint(iPoint).normalize();
                                        //direction to the light
                                        Vec3f l = (lights[j]->getPosition()-iPoint).normalize();
                                        float d = n.dot(l);
                                        if(d<0){ d=0; }
                                    
                                        Vec3f diffuseColor = objects[i]->getMaterial().getDiffuseColor()*lights[j]->getColor()*d;
                                        Vec3f ambientColor = objects[i]->getMaterial().getAmbientColor()*lights[j]->getColor();

                                        Ray lightRay = Ray(lights[j]->getPosition(), (iPoint - lights[j]->getPosition()).normalize()); 
                                        Vec3f r = lightRay.getReflection(n);
                                        Vec3f v = (origin - iPoint);
                                        float s = v.normalize().dot(r.normalize());
                                        if(s<0){ s=0; }

                                        Vec3f specularColor = objects[i]->getMaterial().getSpecularColor()*lights[j]->getSpecularCoefficient()*std::pow(s, objects[i]->getMaterial().getShininess());
                                        currentColor =  diffuseColor + ambientColor + specularColor;
                                        if(currentColor.x > 1) currentColor.x = 1.0f;
                                        if(currentColor.y > 1) currentColor.y = 1.0f;
                                        if(currentColor.z > 1) currentColor.z = 1.0f;
                                    }
                                    else
                                    {
                                        Vec3f ambientColor = objects[i]->getColor()*lights[j]->getAmbientCoefficient();
                                        currentColor =  ambientColor;
                                        if(currentColor.x > 1) currentColor.x = 1.0f;
                                        if(currentColor.y > 1) currentColor.y = 1.0f;
                                        if(currentColor.z > 1) currentColor.z = 1.0f;
                                    }
                                }
                            }
                        } 
                    }

                    img << (int) (currentColor.x * 255)  << " " << (int) (currentColor.y * 255) << " " << (int) (currentColor.z * 255)  << std::endl;
                }
            }
        }
        void addObject(Raytracable* o){ objects.push_back(o); }
        void addLight(Light* l) { lights.push_back(l); }
    private:
        std::vector<Raytracable*> objects;
        std::vector<Light*> lights;
};

#endif 

