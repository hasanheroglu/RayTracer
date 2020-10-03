#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include "vector3.h"
#include "matrix4.h"
#include "triangle.h"
#include "sphere.h"
#include "raytracable.h"
#include "light.h"

#define WIDTH 2000
#define HEIGHT 2000

#define NEAR 0.1
#define FAR 100

float zBuffer[HEIGHT][WIDTH];

void fillZBuffer()
{
    for(size_t i=0; i<HEIGHT; i++)
    {
        for(size_t j=0; j<WIDTH; j++)
        {
            zBuffer[i][j]= 99999.0f;
        }
    }
}

void printZBuffer()
{
    for(size_t i=0; i<HEIGHT; i++)
    {
        for(size_t j=0; j<WIDTH; j++)
        {
            printf("%f ", zBuffer[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    fillZBuffer();
    Vec3f origin(0.0f, 0.0f, 0.0f);

    //Sphere variables
    Vec3f center(3.0f, 0.0f, 6.0f);
    Vec3f sColor(0.0f, 0.7f, 0.0f);

    //Triangle variables
    Vec3f p1(0.5f, 0.3f, 1.0f);
    Vec3f p2(-0.5f, 0.3f, 5.0f);
    Vec3f p3(-0.0f, 0.8f, 4.5f);
    Vec3f tColor(0.4f, 0.0f, 0.0f);

    //Light variables
    Vec3f position(0.0f, 10.0f, -6.0f);
    Vec3f direction(0.0f, -1.0f, 0.0f);
    Vec3f lColor(1.0f, 1.0f, 1.0f);
    Light light(3.0f, 1.0f, 0.3f, 1.0f, position, direction, lColor);
    
    std::vector<Raytracable*> raytracables;
    raytracables.push_back(new Sphere(center, 2.0f, sColor));
    //raytracables.push_back(new Triangle(p1, p2, p3, tColor));

    std::ofstream img("picture.ppm");
    img << "P3" << std::endl;
    img << WIDTH << " " << HEIGHT << std::endl;
    img << "255" << std::endl;

    printf("Starting Raytracing...\n");
    for(int x=HEIGHT/2 - 1; x>=-HEIGHT/2; x--)
    {
        for(int y=-WIDTH/2; y<WIDTH/2; y++)
        {
            Ray ray(origin, (Vec3f((float)y/(WIDTH/2), (float)x/(HEIGHT/2), 1.0f)-origin).normalize());
            Vec3f currentColor(0.5f, 0.5f, 0.5f);            
            
            for(size_t i=0; i<raytracables.size(); i++)
            {
                Vec3f iPoint;
                if(raytracables[i]->intersects(ray, NEAR, FAR, iPoint) == IntersectionStatus::HIT)
                {                    
                    if(iPoint.z < zBuffer[x+HEIGHT/2][y+WIDTH/2])
                    {
                        zBuffer[x+HEIGHT/2][y+WIDTH/2] = iPoint.z;
                        //currentColor = raytracables[i]->getColor();

                        if(light.canSee(iPoint, raytracables))
                        {
                            //normal
                            Vec3f n = raytracables[i]->getNormalForPoint(iPoint).normalize();
                            //direction to the light
                            Vec3f l = (light.getPosition()-iPoint).normalize();
                            float d = n.dot(l);
                            if(d<0){ d=0; }
                        
                            Vec3f diffuseColor = raytracables[i]->getColor()*light.getDiffuseCoefficient()*d;
                            Vec3f ambientColor = raytracables[i]->getColor()*light.getAmbientCoefficient();

                            Ray lightRay = Ray(light.getPosition(), (iPoint - light.getPosition()).normalize()); 
                            Vec3f r = lightRay.getReflection(n);
                            Vec3f v = (origin - iPoint);
                            float s = v.normalize().dot(r.normalize());
                            if(s<0){ s=0; }

                            Vec3f specularColor = raytracables[i]->getColor()*light.getSpecularCoefficient()*std::pow(s, 50);
                            currentColor =  diffuseColor + ambientColor + specularColor;
                            if(currentColor.x > 1) currentColor.x = 1.0f;
                            if(currentColor.y > 1) currentColor.y = 1.0f;
                            if(currentColor.z > 1) currentColor.z = 1.0f;
                        }
                    }
                } 
            }

            img << (int) (currentColor.x * 255)  << " " << (int) (currentColor.y * 255) << " " << (int) (currentColor.z * 255)  << std::endl;
        }
    }
    printf("Raytracing completed...\n");
}