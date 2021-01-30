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
#include "material.h"
#include "camera.h"

#define WIDTH 1000
#define HEIGHT 1000

#define MAX_REFLECTION_COUNT 2

int main()
{
    Vec3f origin(0.0f, 0.0f, -5.0f);

    //Sphere variables
    Vec3f center(0.0f, 0.0f, 10.0f);
    Vec3f sColor(0.0f, 0.7f, 0.0f);
    Sphere* sphere1 = new Sphere(center, 3.0f, sColor);

    //Sphere 2 variables
    Vec3f center2(10.0f, 0.0f, 10.0f);
    Vec3f sColor2(0.7f, 0.0f, 0.7f);
    Sphere* sphere2 = new Sphere(center2, 2.5f, sColor2);

    //Sphere 3 variables
    Vec3f center3(-10.0f, 0.0f, 15.0f);
    Vec3f sColor3(0.1f, 0.2f, 0.6f);
    Sphere* sphere3 = new Sphere(center3, 0.7f, sColor3);

    //Sphere 4 variables
    Vec3f center4(-3.0f, 3.0f, 4.0f);
    Vec3f sColor4(0.7f, 0.0f, 0.7f);
    Sphere* sphere4 = new Sphere(center4, 1.0f, sColor2);

    //Triangle variables
    Vec3f p1(0.5f, 0.3f, 1.0f);
    Vec3f p2(-0.5f, 0.3f, 5.0f);
    Vec3f p3(-0.0f, 0.8f, 4.5f);
    Vec3f tColor(0.4f, 0.0f, 0.0f);

    //Light variables
    Vec3f position(0.0f, 0.0f, -30.0f);
    Vec3f direction(0.0f, -1.0f, 0.0f);
    Vec3f lColor(1.0f, 1.0f, 1.0f);
    Light* light1 = new Light(3.0f, 1.0f, 0.3f, 1.0f, position, direction, lColor);

    //Material 1 variables
    Vec3f ambientColor1(0.3f, 0.5f, 0.0f);
    Vec3f diffuseColor1(0.3f, 0.5f, 0.0f);
    Vec3f specularColor1(1.0f, 1.0f, 1.0f);
    float shininess1 =  100.0f;
    Material* material1 = new Material(ambientColor1, diffuseColor1, specularColor1, shininess1);

    //Material 2 variables
    Vec3f ambientColor2(1.0f, 0.0f, 0.0f);
    Vec3f diffuseColor2(1.0f, 0.0f, 0.0f);
    Vec3f specularColor2(1.0f, 1.0f, 1.0f);
    float shininess2 =  50.0f;
    Material* material2 = new Material(ambientColor2, diffuseColor2, specularColor2, shininess2);

    sphere1->setMaterial(*material1);
    sphere2->setMaterial(*material1);
    sphere3->setMaterial(*material2);
    sphere4->setMaterial(*material2);

    ///Camera variables
    Camera* camera = new Camera(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f), Vec3f(0.0f, 1.0f, 0.0f), 1.0f, 100.0f, WIDTH, HEIGHT, 0.785f);

    std::vector<Raytracable*> raytracables;
    raytracables.push_back(sphere1);
    raytracables.push_back(sphere2);
    //raytracables.push_back(new Triangle(p1, p2, p3, tColor));

    std::vector<Light*> lights;
    lights.push_back(light1);

    Scene* s = new Scene(raytracables, lights);
    s->setCamera(camera);
    s->addObject(sphere3);
    s->addObject(sphere4);
    s->trace();

}