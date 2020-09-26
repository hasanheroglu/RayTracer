#include <iostream>
#include <fstream>
#include <stdio.h>
#include "vector3.h"
#include "matrix4.h"
#include "triangle.h"

#define WIDTH 1920     
#define HEIGHT 1080

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
    Vec3f origin(0.0f, 0.0f, 0.8f);
    Vec3f p1(0.0f, 0.0f, 1.0f);
    Vec3f p2(0.4f, 0.7f, 1.2f);
    Vec3f p3(0.8f, 0.2f, 1.5f);
    Vec3f p4(-0.5f, -0.7f, 1.5f);
    Vec3f color(0.0f, 1.0f, 0.0f);
    Vec3f color1(1.0f, 0.0f, 0.0f);
    Vec3f color2(0.0f, 0.0f, 1.0f);

    Triangle *triangles = new Triangle[3];
    triangles[0] = Triangle(p1, p2, p3, color);
    triangles[1] = Triangle(p1, p2, p4, color1);
    triangles[2] = Triangle(p3, p2, p4, color2);
    std::ofstream img("picture.ppm");
    img << "P3" << std::endl;
    img << WIDTH << " " << HEIGHT << std::endl;
    img << "255" << std::endl;

    printf("Starting Raytracing...\n");
    for(int x=HEIGHT/2 - 1; x>=-HEIGHT/2; x--)
    {
        for(int y=-WIDTH/2; y<WIDTH/2; y++)
        {
            Ray ray(origin, (Vec3f((float)y/(WIDTH/2), (float)x/(HEIGHT/2), 1.0f) - origin).normalize());
            Vec3f currentColor(0.0f, 0.0f, 0.0f);            
            
            for(size_t i=0; i<3; i++)
            {
                float zPoint;
                if(triangles[i].intersects(ray, zPoint))
                {                    
                    if(zPoint < zBuffer[x+HEIGHT/2][y+WIDTH/2])
                    {
                        zBuffer[x+HEIGHT/2][y+WIDTH/2] = zPoint;
                        currentColor = triangles[i].getColor();
                    }
                } 
            }

            img << (int) (currentColor.x * 255)  << " " << (int) (currentColor.y * 255) << " " << (int) (currentColor.z * 255)  << std::endl;
        }
    }
    printf("Raytracing completed...\n");
    //printZBuffer();
}