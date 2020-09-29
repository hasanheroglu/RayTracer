#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "vector3.h"
#include "matrix4.h"
#include "triangle.h"
#include "sphere.h"
#include "raytracable.h"

#define WIDTH 1000    
#define HEIGHT 1000

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
    Vec3f center(0.0f, 0.0f, 6.0f);
    Vec3f sColor(0.0f, 1.0f, 0.0f);

    //Triangle variables
    Vec3f p1(0.5f, 0.3f, 1.0f);
    Vec3f p2(-0.5f, 0.3f, 5.0f);
    Vec3f p3(-0.0f, 0.8f, 4.5f);
    Vec3f tColor(1.0f, 0.0f, 0.0f);

    std::vector<Raytracable*> raytracables;
    raytracables.push_back(new Sphere(center, 2.0f, sColor));
    raytracables.push_back(new Triangle(p1, p2, p3, tColor));

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
            Vec3f currentColor(0.0f, 0.0f, 0.0f);            
            
            for(size_t i=0; i<raytracables.size(); i++)
            {
                float zPoint;
                if(raytracables[i]->intersects(ray, NEAR, FAR, zPoint))
                {                    
                    if(zPoint < zBuffer[x+HEIGHT/2][y+WIDTH/2])
                    {
                        zBuffer[x+HEIGHT/2][y+WIDTH/2] = zPoint;
                        currentColor = raytracables[i]->getColor();
                    }
                } 
            }

            img << (int) (currentColor.x * 255)  << " " << (int) (currentColor.y * 255) << " " << (int) (currentColor.z * 255)  << std::endl;
        }
    }
    printf("Raytracing completed...\n");
}