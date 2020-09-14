#include <iostream>
#include <fstream>
#include <stdio.h>
#include "vector3.h"
#include "matrix4.h"
#include "triangle.h"

#define WIDTH 640
#define HEIGHT 480

int main()
{

    Vec3f origin(0.0f, 0.0f, 0.8f);
    Vec3f p1(-1.0f, 01.0f, 1.0f);
    Vec3f p2(1.0f, 1.0f, 1.0f);
    Vec3f p3(0.5f, 0.0f, 1.0f);
    Vec3f color(0.0f, 1.0f, 0.0f);

    Triangle *triangle = new Triangle(p1, p2, p3, color);

    std::ofstream img("picture.ppm");
    img << "P3" << std::endl;
    img << WIDTH << " " << HEIGHT << std::endl;
    img << "255" << std::endl;

    for(int x=-HEIGHT/2; x<HEIGHT/2; x++)
    {
        for(int y=-WIDTH/2; y<WIDTH/2; y++)
        {
            Ray ray(origin, (Vec3f((float)y/(WIDTH/2), (float)x/(HEIGHT/2), 1.0f) - origin).normalize());

            if(triangle->intersects(ray))
            {
                img << (int) (triangle->getColor().x * 255)  << " " << (int) (triangle->getColor().y * 255) << " " << (int) (triangle->getColor().z * 255)  << std::endl;
            } 
            else
            {
                img << 0 << " " << 0 << " " << 0 << std::endl;
            }
        }
    }
}