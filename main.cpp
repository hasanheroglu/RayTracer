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
#include "scene.h"

#define WIDTH 500
#define HEIGHT 500

#define MAX_REFLECTION_COUNT 2

int main()
{
    Vec3f origin(0.0f, 0.0f, 0.5f);

    //Sphere variables
    Vec3f center(0.0f, 0.0f, 10.0f);
    Vec3f sColor(0.0f, 0.7f, 0.0f);

    //Sphere 2 variables
    Vec3f center2(0.0f, 0.0f, 6.0f);
    Vec3f sColor2(0.7f, 0.0f, 0.7f);

    //Sphere 3 variables
    Vec3f center3(0.0f, 0.0f, 3.0f);
    Vec3f sColor3(0.1f, 0.2f, 0.6f);

    //Triangle variables
    Vec3f p1(0.5f, 0.3f, 1.0f);
    Vec3f p2(-0.5f, 0.3f, 5.0f);
    Vec3f p3(-0.0f, 0.8f, 4.5f);
    Vec3f tColor(0.4f, 0.0f, 0.0f);

    //Light variables
    Vec3f position(10.0f, 0.0f, -10.0f);
    Vec3f direction(0.0f, -1.0f, 0.0f);
    Vec3f lColor(1.0f, 1.0f, 1.0f);
    
    std::vector<Raytracable*> raytracables;
    raytracables.push_back(new Sphere(center, 5.0f, sColor));
    raytracables.push_back(new Sphere(center2, 2.5f, sColor2));
    //raytracables.push_back(new Triangle(p1, p2, p3, tColor));

    std::vector<Light*> lights;
    lights.push_back(new Light(3.0f, 1.0f, 0.3f, 1.0f, position, direction, lColor));

    Scene* s = new Scene(raytracables, lights);
    s->addObject(new Sphere(center3, 0.7f, sColor3));
    s->trace(WIDTH, HEIGHT, origin);

}